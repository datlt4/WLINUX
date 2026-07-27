# x11vnc + noVNC — Stream màn hình Ubuntu ra browser trong LAN

Stream một màn hình cụ thể từ máy Ubuntu (nhiều màn hình) ra bất kỳ browser nào trong mạng nội bộ. Không cần cài VNC viewer ở máy xem.

- **Host**: Ubuntu, session **Xorg** (không phải Wayland)
- **Client**: browser bất kỳ
- **Giao thức**: RFB (VNC) → WebSocket → noVNC

---

## 1. Yêu cầu

Kiểm tra bạn đang chạy Xorg, không phải Wayland:

```bash
echo $XDG_SESSION_TYPE   # phải in ra: x11
```

Nếu in ra `wayland`: logout, ở màn hình đăng nhập bấm bánh răng ở góc dưới phải, chọn **Ubuntu on Xorg**, rồi đăng nhập lại. `x11vnc` không hoạt động trên Wayland.

## 2. Cài đặt

```bash
sudo apt update
sudo apt install -y x11vnc novnc websockify net-tools tmux tmuxinator
```

Kiểm tra noVNC đã có đúng chỗ:

```bash
ls /usr/share/novnc/vnc.html
```

## 3. Tạo mật khẩu VNC

```bash
mkdir -p ~/.vnc
x11vnc -storepasswd
chmod 600 ~/.vnc/passwd
```

Nhập mật khẩu 2 lần, chọn `y` khi nó hỏi lưu vào `~/.vnc/passwd`.

> **Lưu ý**: giao thức RFB cổ điển chỉ dùng **8 ký tự đầu**, ký tự thứ 9 trở đi bị bỏ âm thầm. Nên đặt đúng 8 ký tự.

Cách một dòng (mật khẩu sẽ nằm trong shell history):

```bash
x11vnc -storepasswd 'matkhau8' ~/.vnc/passwd
```

## 4. Xác định màn hình cần stream

`-clip` nhận **dạng chữ** `xineramaN` — N là chỉ số sub-screen, x11vnc tự hỏi X server màn đó nằm ở đâu và to bao nhiêu rồi tự tính vùng cắt:

```bash
-clip xinerama0     # màn thứ nhất
-clip xinerama1     # màn thứ hai
-clip xinerama2     # màn thứ ba
-clip reset         # bỏ clip, stream toàn bộ framebuffer
```

Ưu điểm lớn: **không phải cập nhật gì khi bố trí màn hình thay đổi**. Cắm rút màn, kéo màn sang vị trí khác, đổi độ phân giải — `xinerama0` vẫn tự trỏ đúng. Với toạ độ tuyệt đối thì mọi offset đều sai và phải sửa lại tay.

### Xác định N nào là màn nào

Chỉ số Xinerama **không nhất thiết trùng** thứ tự trong `xrandr --listmonitors`, cũng không nhất thiết theo thứ tự trái-sang-phải. Cách nhanh nhất là thử trực tiếp:

```bash
# Thử từng chỉ số, mỗi lần mở noVNC xem ra màn nào
x11vnc -R clip:xinerama0
x11vnc -R clip:xinerama1
x11vnc -R clip:xinerama2
```

Ghi lại kết quả rồi điền vào bảng này để lần sau không phải mò:

| Chỉ số | Màn hình thực tế | Độ phân giải |
|---|---|---|
| `xinerama0` | | |
| `xinerama1` | | |
| `xinerama2` | | |

Muốn biết x11vnc thấy bao nhiêu sub-screen, xem log:

```bash
grep -i xinerama /tmp/x11vnc-5900.log
```

Kỳ vọng: `Xinerama: number of sub-screens: 3`. Nếu ra `1` thì X server đang gộp cả 3 màn thành một sub-screen duy nhất — khi đó `xinerama0` = toàn bộ framebuffer và `xinerama1/2` không tồn tại. Xem mục 12 để xử lý.

### Tham khảo: layout hiện tại

```bash
xrandr --listmonitors
```

```
Monitors: 3
 0: +*DP-2   2560/527x1440/296+1920+0   DP-2      2K
 1: +DP-0    2560/527x1440/296+4480+0   DP-0      2K
 2: +HDMI-1  1920/508x1080/286+0+0      HDMI-1    FHD
```

Chỉ dùng khi cần đối chiếu tên thiết bị hoặc debug — không cần copy số vào config.

## 5. Chạy nhanh (thủ công)

Terminal 1 — x11vnc:

```bash
x11vnc -display :0 -auth guess \
       -clip xinerama0 \
       -viewonly -shared -forever \
       -rfbport 5900 -rfbauth ~/.vnc/passwd \
       -xkb -repeat -nocursorshape -cursor most \
       -xrandr resize
```

Terminal 2 — websockify:

```bash
websockify --web=/usr/share/novnc 8002 localhost:5900
```

Mở browser ở máy khác:

```
http://<IP-UBUNTU>:8002/vnc.html?autoconnect=1&resize=scale&view_only=1
```

Lấy IP: `hostname -I | awk '{print $1}'`

---

## 6. Bảng tham số x11vnc

### Bắt buộc / nên có

| Tham số | Tác dụng |
|---|---|
| `-display :0` | X display cần capture. Gần như luôn là `:0`. |
| `-auth guess` | Tự tìm file `Xauthority`. **Bắt buộc** nếu chạy qua SSH, cron, systemd, hoặc tmux khởi động từ session khác. |
| `-clip xinerama0` | **Cách dùng chính.** Chỉ capture một sub-screen (một màn hình) thay vì cả framebuffer ghép. Giá trị: `xinerama0`, `xinerama1`, `xinerama2`..., hoặc `reset` để bỏ clip. Tự đúng khi layout màn hình thay đổi. |
| `-clip WxH+X+Y` | Dạng toạ độ tuyệt đối, ví dụ `1920x1080+0+0`. Chỉ dùng làm phương án dự phòng khi X server không báo đúng sub-screen — xem mục 12. |
| `-rfbport 5900` | Port VNC. Nhiều màn → mỗi màn một port (5900, 5901, 5902...). |
| `-rfbauth ~/.vnc/passwd` | File mật khẩu. Bỏ tham số này là **mở toang không mật khẩu**. |
| `-forever` | Không thoát khi client ngắt kết nối. Không có nó thì phải chạy lại sau mỗi lần đóng tab. |
| `-shared` | Cho nhiều client xem cùng lúc. Không có nó, client mới sẽ kick client cũ. |

### Chế độ xem / điều khiển

| Tham số | Tác dụng |
|---|---|
| `-viewonly` | **Chặn điều khiển ở phía server.** Client không thể gửi chuột/bàn phím kể cả khi cố tình. Bỏ tham số này để cho phép điều khiển. |
| `-xkb` | Xử lý bàn phím qua XKEYBOARD. Giúp gõ đúng `@ # [ ] { }` và ký tự có dấu. Chỉ cần khi cho điều khiển. |
| `-repeat` | Cho phép giữ phím để lặp (Backspace, phím mũi tên). Mặc định x11vnc **tắt** tính năng này. |
| `-noxkb` | Ngược lại của `-xkb`, dùng khi map bàn phím bị lỗi lạ. |

### Con trỏ chuột

| Tham số | Tác dụng |
|---|---|
| `-nocursorshape` | **Vẽ con trỏ vào ảnh.** Cần thiết nếu muốn thấy con trỏ của người ngồi ở máy remote. Mặc định x11vnc chỉ gửi *hình dạng* con trỏ rồi client tự vẽ theo chuột **local**, nên không thấy chuột remote di chuyển. |
| `-cursor most` | Cố hiển thị đúng hình dạng con trỏ trong nhiều ngữ cảnh nhất (I-beam, tay, mũi tên resize). Dùng `-cursor arrow` nếu chỉ cần biết vị trí (nhẹ hơn chút). |
| `-nocursor` | Ẩn con trỏ hoàn toàn. |

### Hiệu năng

| Tham số | Tác dụng |
|---|---|
| `-wait 10` | Khoảng nghỉ giữa 2 lần poll màn hình (ms). Nhỏ hơn = mượt hơn + tốn CPU hơn. LAN dùng `10` là mượt. Mặc định 30. |
| `-speeds lan` | Khai báo tốc độ mạng để x11vnc tự tinh chỉnh. Giá trị: `modem`, `dsl`, `lan`. |
| `-defer 10` | Gộp các update trong khoảng này rồi gửi 1 lần (ms). |
| `-noxdamage` | Tắt XDAMAGE, dùng khi có lỗi vẽ hình sai. Tốn CPU hơn nhiều. |
| `-xrandr resize` | Tự thích nghi khi bố trí màn hình thay đổi (cắm/rút màn) thay vì thoát. **Vùng `-clip` vẫn phải đặt lại thủ công** vì offset đã đổi. |
| `-fixscreen V=3` | Tự vẽ lại toàn màn hình mỗi 3 giây. Dùng khi hay bị "rác" hiển thị. |

### ⚠️ KHÔNG dùng với noVNC

| Tham số | Vì sao |
|---|---|
| `-ncache 10` | **Gây dải đen dày phía dưới ảnh.** Tính năng này nới framebuffer cao thêm rất nhiều để chứa cache pixel của cửa sổ ẩn. Chỉ vài client cũ (SSVNC, TightVNC) mới hiểu và ẩn vùng đó — **noVNC thì không**, nó vẽ luôn cả vùng cache như một phần desktop, làm tỉ lệ khung hình sai và không thể phóng khít. Dòng `x11vnc -ncache 10 ...` mà x11vnc in ra trong log chỉ là quảng cáo tính năng, không phải khuyến nghị. |
| `-ncache_cr` | Cùng lý do trên. |

### Tiện ích khác

| Tham số | Tác dụng |
|---|---|
| `-bg` | Chạy nền, tách khỏi terminal. **Đừng dùng trong tmux/tmuxinator** — pane sẽ đóng ngay và bạn mất log. |
| `-o /tmp/x11vnc.log` | Ghi log ra file. |
| `-localhost` | Chỉ nhận kết nối từ chính máy đó. Kết hợp với websockify chạy cùng máy → chỉ port web lộ ra LAN. Rất nên dùng. |
| `-allow 192.168.1.` | Whitelist theo IP prefix. |
| `-nevershared` | Ngược lại của `-shared`. |
| `-ultrafilexfer` | Bật truyền file (cần client hỗ trợ, noVNC không có). |

---

## 7. Đổi tham số khi đang chạy (không cần restart)

x11vnc nhận lệnh remote control qua cờ `-R`. Mở terminal khác và chạy:

```bash
x11vnc -R clip:xinerama0           # nhảy sang màn 0
x11vnc -R clip:xinerama1           # màn 1
x11vnc -R clip:xinerama2           # màn 2
x11vnc -R clip:reset               # bỏ clip, xem cả 3 màn
x11vnc -R viewonly:0               # bật cho phép điều khiển
x11vnc -R viewonly:1               # khoá lại chỉ xem
x11vnc -R cursorshape:0            # vẽ con trỏ vào ảnh
x11vnc -R cursor:most
x11vnc -R wait:10
x11vnc -R stop                     # tắt server
```

Nếu `-R` không có tác dụng, khởi động lại với tham số đầy đủ.

---

## 8. Tham số URL của noVNC

```
http://<IP>:8002/vnc.html?autoconnect=1&resize=scale&view_only=1&reconnect=1
```

| Tham số | Giá trị | Ghi chú |
|---|---|---|
| `autoconnect` | `1` | Tự kết nối, không cần bấm nút Connect |
| `resize` | `scale` / `remote` / `off` | Dùng `scale` (Local Scaling). **Đừng dùng `remote`** — nó cần server đổi được kích thước desktop, mà x11vnc khi đang `-clip` thì không làm được |
| `view_only` | `1` / `0` | Khoá điều khiển ở phía client |
| `reconnect` | `1` | Tự nối lại khi mất kết nối |
| `password` | `xxx` | Điền sẵn mật khẩu (kém an toàn, lộ trong URL và history) |
| `quality` | `0`–`9` | 6 là mặc định |
| `compression` | `0`–`9` | 2 là mặc định |

> **Cái bẫy hay gặp**: noVNC lưu setting vào **localStorage của browser**. Nếu bạn từng tick "View Only" thì nó giữ nguyên dù URL đã đổi, và ô đó **bị khoá khi đang kết nối** nên bấm không được. Cách sửa: bấm **Disconnect** trước rồi mới bỏ tick, hoặc mở bằng **cửa sổ ẩn danh**, hoặc F12 → Console → `localStorage.clear()` rồi F5.

Trong sidebar noVNC có sẵn:
- **Clipboard** — dán text vào đây để gửi sang máy Ubuntu (browser không cho web tự đọc clipboard hệ thống)
- **Keyboard** — gửi Ctrl+Alt+Del và các tổ hợp bị browser chiếm
- **Fullscreen**

---

## 9. Nhiều màn hình cùng lúc

Mỗi màn một cặp port. Xem file `vnc-3mon.yml` để chạy cả 3 bằng tmuxinator.

| `-clip` | Port VNC | Port web | URL |
|---|---|---|---|
| `xinerama0` | 5900 | 8002 | `http://<IP>:8002/vnc.html?autoconnect=1&resize=scale` |
| `xinerama1` | 5901 | 8003 | `http://<IP>:8003/vnc.html?autoconnect=1&resize=scale` |
| `xinerama2` | 5902 | 8004 | `http://<IP>:8004/vnc.html?autoconnect=1&resize=scale` |

Lưu ý: mỗi instance là một lần capture + encode riêng, nên CPU nhân theo số luồng. Desktop tĩnh thì mỗi cái chỉ 1–3%. Chỉ chạy đủ số màn bạn thực sự cần xem.

---

## 10. Chạy bằng tmuxinator

Copy config vào đúng chỗ:

```bash
mkdir -p ~/.config/tmuxinator
cp vnc.yml vnc-3mon.yml ~/.config/tmuxinator/
```

Chạy:

```bash
tmuxinator start vnc          # 1 màn (FHD)
tmuxinator start vnc-3mon     # cả 3 màn
```

Các lệnh hữu ích:

```bash
tmuxinator stop vnc       # tắt toàn bộ
tmuxinator edit vnc       # sửa config
tmux attach -t vnc        # vào lại session
# Ctrl-b d               → detach (server vẫn chạy)
# Ctrl-b 0/1/2           → chuyển window
```

Sửa tham số: mở `~/.config/tmuxinator/vnc.yml`, đổi các biến trong khối `pre_window` ở đầu file (clip, port, viewonly...), rồi `tmuxinator stop vnc && tmuxinator start vnc`.

---

## 11. Bảo mật

Khi **có bật điều khiển** (bỏ `-viewonly`), ai vào được port web là điều khiển được máy bạn.

```bash
# 1. Ép x11vnc chỉ nghe localhost — websockify cùng máy vẫn nối được
#    (đã có trong config mẫu)
-localhost

# 2. Chỉ mở port web cho LAN
sudo ufw allow from 192.168.1.0/24 to any port 8002 proto tcp
sudo ufw enable

# 3. Bật TLS cho websockify (khuyến nghị nếu cho điều khiển)
openssl req -new -x509 -days 3650 -nodes -out ~/.vnc/novnc.pem \
        -keyout ~/.vnc/novnc.pem -subj "/CN=vnc.local"
chmod 600 ~/.vnc/novnc.pem
websockify --web=/usr/share/novnc --cert=~/.vnc/novnc.pem 8002 localhost:5900
# → truy cập bằng https://<IP>:8002/vnc.html
```

Mặc định WebSocket của noVNC là `ws://` **không mã hoá**. Mật khẩu VNC đã được hash theo giao thức, nhưng toàn bộ hình ảnh và từng phím bạn gõ đi dạng thô trên mạng.

---

## 12. Xử lý sự cố

| Hiện tượng | Nguyên nhân | Cách sửa |
|---|---|---|
| Dải đen dày dưới ảnh, không phóng khít | Đang dùng `-ncache` | Bỏ `-ncache` và `-ncache_cr` |
| `xinerama0` ra sai màn so với mong đợi | Chỉ số Xinerama không theo thứ tự vật lý | Thử `x11vnc -R clip:xinerama1` / `xinerama2` để tìm đúng chỉ số |
| `xinerama0` ra cả 3 màn ghép lại, `xinerama1/2` vô tác dụng | X server gộp 3 màn thành 1 sub-screen. Log báo `Xinerama: number of sub-screens: 1` | Xem khối "Khi Xinerama không hoạt động" ngay dưới bảng này |
| Dải đen ở dưới ảnh dù đã clip đúng | Đang dùng `-ncache` | Bỏ `-ncache` |
| noVNC hỏi mật khẩu mãi không vào | File `~/.vnc/passwd` chưa tồn tại. Log báo `Couldn't read password file` | Chạy `x11vnc -storepasswd` |
| Mật khẩu đúng mà vẫn sai | Mật khẩu dài hơn 8 ký tự | Đặt lại đúng 8 ký tự |
| Không điều khiển được | Còn `-viewonly` ở server, **hoặc** noVNC còn tick View Only trong localStorage | `ps aux \| grep x11vnc` để kiểm tra; disconnect rồi bỏ tick; hoặc mở tab ẩn danh |
| Ô View Only bị xám không bấm được | noVNC khoá setting khi đang kết nối | Bấm Disconnect trước |
| Không thấy con trỏ của người ở máy remote | Thiếu `-nocursorshape` | Thêm `-nocursorshape -cursor most` |
| Thấy 2 con trỏ | Bình thường: con trỏ browser + con trỏ vẽ trong ảnh | F12 → Console → `document.getElementById('noVNC_canvas').style.cursor='none'` |
| `listen6: bind: Address already in use` | Chỉ IPv6 port bị chiếm, IPv4 vẫn OK | Vô hại. Muốn sạch thì `pkill x11vnc` trước |
| `selection_send: no send: uninitialized clients` | Thông báo về clipboard | Vô hại, đúng khi đang `-viewonly` |
| `XOpenDisplay failed` khi chạy qua SSH/systemd | Không tìm được Xauthority | Thêm `-auth guess`, hoặc `-auth /run/user/$(id -u)/gdm/Xauthority` |
| x11vnc thoát ngay khi cắm/rút màn hình | Layout thay đổi | Thêm `-xrandr resize` |
| Cửa sổ bị cắt nửa | Cửa sổ nằm vắt qua 2 màn | Không tránh được, bản chất là cắt vùng pixel |
| Gõ tiếng Việt ra ký tự sai | 2 bộ gõ chồng nhau | Chỉ dùng bộ gõ trên máy Ubuntu (ibus-bamboo/unikey), tắt bộ gõ ở máy client |

### Khi Xinerama không hoạt động

Nếu log báo `Xinerama: number of sub-screens: 1` trong khi bạn có 3 màn, X server đang gộp tất cả thành một sub-screen. Với driver NVIDIA proprietary, bật lại thông tin Xinerama:

```bash
sudo nvidia-xconfig --nvidia-xinerama-info
# hoặc thêm vào /etc/X11/xorg.conf, Section "Screen":
#   Option "nvidiaXineramaInfo" "true"
```

Rồi logout/login và kiểm tra lại. Nếu vẫn không được, dùng toạ độ tuyệt đối làm phương án dự phòng:

```bash
xrandr --listmonitors
# 0: +*DP-2   2560/527x1440/296+1920+0   →  -clip 2560x1440+1920+0
# 1: +DP-0    2560/527x1440/296+4480+0   →  -clip 2560x1440+4480+0
# 2: +HDMI-1  1920/508x1080/286+0+0      →  -clip 1920x1080+0+0
```

Cách đọc: `2560/527x1440/296+1920+0` → độ phân giải **2560x1440**, offset **+1920+0** (bỏ qua hai số kích thước vật lý mm). Nhớ rằng nếu màn thấp hơn bị canh giữa theo chiều dọc thì offset Y sẽ khác 0 (ví dụ `+180`), và mỗi lần đổi bố trí màn hình bạn phải sửa lại toàn bộ số này bằng tay — đó là lý do `xineramaN` tiện hơn.

Con trỏ khó thấy qua stream? Chạy trên máy Ubuntu:

```bash
gsettings set org.gnome.desktop.interface cursor-size 48
gsettings set org.gnome.desktop.peripherals.mouse locate-pointer true
# → nhấn Ctrl là có vòng tròn nhấp nháy quanh con trỏ
```

Xem log:

```bash
tail -f /tmp/x11vnc.log
grep -i "geometry\|desktop is\|clip" /tmp/x11vnc.log
```

Kiểm tra kích thước framebuffer đang stream có đúng không (không được cao bất thường kiểu `1920x11880`):

```bash
grep -i "framebuffer\|initialize_screen" /tmp/x11vnc.log
```
