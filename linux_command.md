## Lệnh cơ bản 1.

1. Chuyển sang giao diện GUI:

        $ startx

1. Khởi động lại:

        $ sudo reboot

1. Tắt RaPi:

        $ sudo halt

1. Tắt RaPi:

        $ sudo shutdown -h now

1. Đổi mật khẩu:

        $ sudo passwd root
        $ sudo passwd <userName>

## Secure Shell (SSH)

1. Install

        $ sudo apt-get install openssh-server openssh-client -y

1. Access

        $ ssh <username>@<hosname_ip>

1. SSH configuration

        $ sudo /etc/ssh/sshd_config

1. See status of OpenSSH server

        $ sudo /etc/init.d/ssh status
        $ sudo service ssh status
        $ sudo systemctl status ssh

1. Start OpenSSH server

        $ sudo /etc/init.d/ssh start
        $ sudo service ssh start
        $ sudo systemctl start ssh

1. Stop OpenSSH server

        $ sudo /etc/init.d/ssh stop
        $ sudo service ssh stop
        $ sudo systemctl stop ssh

1. Restart OpenSSH server

        $ sudo /etc/init.d/ssh restart
        $ sudo service ssh restart
        $ sudo systemctl restart ssh

## SSH ngrok

1. Run ngrok server at remote Linux Machine

       $ ngrok tcp 22
       Forwarding tcp://0.tcp.ngrok.io:13212 -> localhost:22

1. Run SSH client on system to connect remote ssh running host

       $ ssh user@0.tcp.ngrok.io -p 13212

1. Connect to the nearest data center around the world

       $ ngrok tcp --region=ap 22
       Forwarding tcp://0.tcp.ap.ngrok.io:12681-> localhost:22

1. Connect to remote system by ssh to nearest ap (asia pacific) region end-point( 0.tcp.ap.ngrok.io ).

       $ ssh user@0.tcp.ap.ngrok.io -p 12681

1. Get tunnels status
       
       $ curl -s http://localhost:4040/api/tunnels | \
           python3 -c \
             "import json, sys, os, pwd; \
             username=pwd.getpwuid(os.getuid()).pw_name;\
             print(json.load(sys.stdin)['tunnels'][0]['public_url'].\
             replace('tcp://', f'ssh {username}@').\
             replace(':', ' -p '))"

## [Create SSH tunel to a running colab notebook](https://github.com/lamhoangtung/colab_ssh)
1. Generate `id_rsa.pub` of **your machine**

       $ ssh-keygen
       $ cat /home/${USER}/.ssh/id_rsa.pub

2. [Install `cloudflared`](https://developers.cloudflare.com/argo-tunnel/getting-started/installation) on **your machine**

       $ wget https://bin.equinox.io/c/VdrWdbjqyF/cloudflared-stable-linux-amd64.deb
       $ sudo dpkg -i cloudflared-stable-linux-amd64.deb
 
3. Create a new Colab notebook with a single cell

       !pip3 install linus_colab_ssh
       
       from colab_ssh import setup_ssh, loop_forever
       public_key = '<YOUR_PUBLIC_SSH_KEY>'
       setup_ssh(public_key)
       loop_forever()

## SCP command to Sercurely Tranfer Files

1. SCP Command Syntax

        scp [OPTION] <user>@<SRC_HOST>:file1  <user2>@<DEST_HOST>:file2

    |Option |Description                                                            |
    |:-----:|-----------------------------------------------------------------------|
    |-C     |Enable Compression                                                     |
    |-c     |encrypt the files                                                      |
    |-i     |identity File or private key                                           |
    |-l     |limit the bandwidth while copying                                      |
    |-P     |ssh port number of target host                                         |
    |-p     |Preserves permissions, modes and access time of files while copying    |
    |-q     |Suppress warning message of SSH                                        |
    |-r     |Copy files and directories recursively                                 |
    |-v     |verbose output                                                         |

1. Copy a file from local system to remote system using scp

        $ scp jdk-linux-x64_bin.rpm root@172.20.10.8:/opt

1. Copy a file from remote System to local system using scp

        $ scp root@172.20.10.8:/root/Technical-Doc-RHS.odt /tmp

1. Verbose Output while transferring files using scp (-v)

        $ scp -v jdk-linux-x64_bin.rpm root@172.20.10.8:/opt

1. Transfer multiple files to remote system

        $ scp install.txt index.html jdk-linux-x64_bin.rpm root@172.20.10.8:/mnt

1. Transfer files across two remote hosts

        $ scp pkumar@172.20.10.9:~/backup-Oct.zip root@172.20.10.8:/tmp

1. Copy files and directories recursively (*-r*)

        $ scp -r Downloads root@172.20.10.8:/opt

1. Increase transfer speed by enabling compression (*-C*)

        $ scp -r -C  Downloads  root@172.20.10.8:/mnt

1. Limit bandwidth while copying (*-l*)

        $ scp -l 500 jdk-linux-x64_bin.rpm root@172.20.10.8:/var

1. Specify different ssh port while scp (*-P*)

        $ scp -P 2022  jdk-linux-x64_bin.rpm  root@172.20.10.8:/var

1. Preserves permissions, modes and access time of files while copying ( -p)

        $ scp -p  jdk-linux-x64_bin.rpm  root@172.20.10.8:/var/tmp

1. Transferring files in quiet mode (-q) in scp - suppress transfer progress, warning and diagnostic messages of ssh

        $ scp -q -r Downloads root@172.20.10.8:/var/tmp

1. Use Identify file in scp while transferring ( -i )

        $ scp -i my_key.pem -r Downloads root@172.20.10.8:/root

1. Use different ‘ssh_config’ file in scp ( -F)

        $ scp -F /home/pkumar/new_ssh_config -r Downloads root@172.20.10.8:/root

1. Use Different Cipher in scp command (-c)

        $ scp -c 3des-cbc -r Downloads root@172.20.10.8:/root

1. [SCP bỏ qua hỏi password](https://minhng.info/ubuntu/ssh-scp-bo-qua-hoi-password-ubuntu.html)



## RSYNC (remote sync) in Linux

[Reference](https://www.linuxtechi.com/rsync-command-examples-linux/#:~:text=Linux%20geeks%20generally%20use%20rsync,require%20root%20or%20sudo%20privileges.. )

1. options

    |Option |           |Description                                                                    |
    |:-----:|-----------|-------------------------------------------------------------------------------|
    |-v     |--verbose  |Verbose output                                                                 |
    |-q     |--quite    |Suppress message output                                                        |
    |-a     |--archive  |Archive files and directory while synchronizing                                |
    |-r     |--recursive|Sync files and directories recursively                                         |
    |-b     |--backup   |Take the backup during synchronization                                         |
    |-u     |--update   |Don’t copy the files from source to destination if destination files are newer |
    |-l     |--links    |Copy symlinks as symlinks during the sync                                      |
    |-n     |--dry-run  |Perform a trial run without synchronization                                    |
    |-e     |--rsh=ssh  |Mention the remote shell to use in rsync                                       |
    |-z     |--compress |Compress file data during the transfer                                         |
    |-h     |--human-readable|Display the output numbers in a human-readable format                     |
    |       |--progress|Show the sync progress during transfer                                          |
    |-i     ||List the difference in files and directories between source and destination               |
    |-P     ||Resume large file transfer after getting failed in scp                                    |

1. RSYNC Command Syntax:

    - Local Sync:

            $ rsync [options] Source Destination

    - Remote Sync Pull:

            $ rsync [options] <User_Name>@<Remote-Host>:<Source-File-Dir> <Destination>

    - Remote Sync Push:

            $ rsync [Options] <Source-Files-Dir> <User_Name>@<Remote-Host>:<Destination>

1. Example

    - Copy or Sync files locally

            $ rsync -zvh  /home/pkumar/OpenStack-Networking.pdf  /opt/backup

    - Copy or Sync directory locally

        - Create pkumar directory

                $ rsync -zavh  /home/pkumar  /opt/backup

        - Not create pkumar directory

                $ rsync -zavh  /home/pkumar/  /opt/backup

    - Copy files & directories recursively locally

            $ rsync -zavh  /home/pkumar/  /opt/backup
            $ rsync -zrvh  /home/pkumar/  /opt/backup

    - Copy or Sync files and directories from remote machine to local system

            $ rsync -zarvh  root@192.168.1.29:/opt/rpms_db  /tmp

    - Display Synchronization progress in rsync command output

            $ rsync -avh --progress  root@192.168.1.29:/opt/rpms_db  /tmp

    - Specify remote shell during synchronization (rsync -e ssh) - secure communication between source to destination machine

            $ rsync -zarvh -e ssh  root@192.168.1.29:/opt/rpms_db  /tmp

    - Resume large file transfer after getting failed in scp

            $ rsync -P --rsh=ssh  root@192.168.1.29:/root/ubuntu-18.04-desktop-amd64.iso  /opt

    - Do not sync/copy the modified file at destination

            $ rsync -avzu  root@192.168.1.29:/opt/techi  /home/pkumar/techi

    - Do not sync/copy the modified file at destination

            $ rsync -avzu  root@192.168.1.29:/opt/techi  /home/pkumar/techi

    - Copy or sync files and directories from local to remote system

            $ rsync -zarvh  /home/pkumar/techi  root@192.168.1.29:/opt

    - Copy the directory structure without copying files

            $ rsync -av -f"+ */" -f"- *"  /home/pkumar  root@192.168.1.29:/opt/

    - Delete files at destination if it is not present in source (–delete)\

            $ rsync -avz --delete  /opt/rpms_db  root@192.168.1.28:/tmp/rpms_db

    - Put limit on file transfer size (–max-size)

            $ rsync -avz --max-size='500K'  /opt/rpms_db  root@192.168.1.28:/tmp

    - Remove files from source after synchronization (–remove-source-files)

            $ rsync --remove-source-files -zvh  /home/pkumar/techi.tgz  root@192.168.1.29:/opt

    - Dry run rsync command before actual synchronization

            $ rsync --dry-run --remove-source-files -zvh  /home/pkumar/projects.tar  root@192.168.1.29:/opt

    - Include and Exclude files during synchronization with rsync

            $ rsync -avz -e ssh --include '*.pdf *.rpm' --exclude '*.png'  /home/pkumar/techi  root@192.168.1.29:/opt

    - Put restriction on data transfer speed in rsync (–bwlimit=<KB/s>)

            $ rsync -avz --progress --bwlimit=600  /home/pkumar/techi  root@192.168.1.29:/opt

    - View the difference in files & directories between source and destination

            $ rsync -avzi  /home/pkumar/techi  root@192.168.1.29:/opt



## Linux tmux command

The Linux tmux command is a terminal multiplexer, allow you to have multiple windows within a single terminal window, and to jump back and forth between them.. In tmux, you will be working with sessions, windows and panes.

[Reference](https://phoenixnap.com/kb/tmux-tutorial-install-commands)

1. Start new TMUX Session

        $ tmux

1. Start new named Session

        $ tmux new -s Session_name
        $ tmux rename-session -t old_name Session_name

1. Suspend TMUX

        [ctrl + b] + [ctrl + z]

1. Split pane TMUX

    - split the screen horizontally

            [ctrl + b] + "

    - split the screen vertically

            [ctrl + b] + %

1. Kill session

        [Ctrl + d]
        $ tmux kill-session -t Session_name
        $ tmux kill-session -a

1. Moving Between Panes

    - Cách 1

            [ctrl + b] + o

    - Có thể chuyển các pane bằng số

            #number

    - display order number

            [ctrl + b] + q

1. Zoom in to Pane

    - Tmux can be used to keep a process working in background. Detach from current session

        - tmux detach

                [ctrl + b] + d

        - re-attach

                $ tmux attach
                $ tmux a -t Session_name
        - make a panel go full screen
                [ctrl + b] + z

1. List active Sessions

        $ tmux ls

1. Create new full screen window

        [ctrl + b] + c

1. Rename window

        [ctrl + b] + ,

1. Switch between window

    - next windows

          [ctrl + b] + n

    - previous windows

          [ctrl + b] + p

1. Display list of Windows

       [ctrl + b] + w

1. Close a Window

       [ctrl + b] + &

## Tmuxinator configuration

- Install tmuxinator

      $ sudo apt --assume-yes install ruby
      $ gem install tmuxinator -v 1.1.5
      $ export EDITOR="/bin/nano"
      $ export SHELL='/bin/bash'
      $ tmuxinator doctor

- Create or edit projects

      tmuxinator new [project]
      tmuxinator new --local [project]

  `--local`: Create or edit a local project where the config file will be stored in the current working directory instead of the default project configuration file location.

- Start a session

      tmuxinator start [project] -n [name] -p [project-config]

`[project-config]` : path to `.yaml` file in local file system.

- Configuration

      # /home/m/.config/tmuxinator/HNIW.yml
      
      name: HNIW
      root: ~/

      windows:
        - w1:
            layout: 3e7d,272x64,0,0{194x64,0,0,0,77x64,195,0[77x23,195,0,2,77x40,195,24,3]}
            panes:
              - main:
                - neofetch
              - htop:
                - htop
              - nvtop:
                - nvtop
        - w2:
            root: ~/Documents/DL-with-pytorch-code
            panes:
              - conda acitvate M

  `layout`: can be one of [5 preset tmux window layout](https://tao-of-tmux.readthedocs.io/zh_CN/latest/manuscript/06-window.html#layouts-window-layouts), or can be retrieved by `tmux list-windows`


## Crontab

1. Create and edit cron directory

       
       # Example of job definition:
       # .---------------- minute (0 - 59)
       # |  .------------- hour (0 - 23)
       # |  |  .---------- day of month (1 - 31)
       # |  |  |  .------- month (1 - 12) OR jan,feb,mar,apr ...
       # |  |  |  |  .---- day of week (0 - 6) (Sunday=0 or 7) OR sun,mon,tue,wed,thu,fri, sat
       # |  |  |  |  |
       # *  *  *  *  *  user-name  command-to-be-executed

1. Scheduling tricks

       01 01 * * * /usr/local/bin/rsbu -vbd1 ; /usr/local/bin/rsbu -vbd2

       03 05 * * * /sbin/hwclock --systohc

       25 04 1 * * /usr/bin/dnf -y update

       00 15 * * Thu /usr/local/bin/mycronjob.sh

       02 03 1 1,4,7,10 * /usr/local/bin/reports.sh

       01 09-17 * * * /usr/local/bin/hourlyreminder.sh

       # run every 5 minutes during any even hours between 8 am to 6pm.
       */5 08-18/2 * * * /usr/local/bin/mycronjob.sh

       # run a job as the user "W"
       04 07 * * * W /usr/local/bin/mycronjob.sh

1. Shortcuts
  
       @reboot : Run once after reboot.
       @yearly : Run once a year, ie. 0 0 1 1 *
       @annually : Run once a year, ie. 0 0 1 1 *
       @monthly : Run once a month, ie. 0 0 1 * *
       @weekly : Run once a week, ie. 0 0 * * 0
       @daily : Run once a day, ie. 0 0 * * *
       @hourly : Run once an hour, ie. 0 * * * *


## Tree command

1. Install

        $ sudo apt-get install tree -y

1. Show only the directories

        $ tree -d

1. Show all file including hidden dot files/

        $ tree -a

1. Limit the depth of recursion

        $ tree -L 2

1. Manual

        $ man tree


## Wireless Connection

1. Installation

        $ sudo apt-get install network-manager

1. Establish a Wireless Connection

    - Turn on wifi

            $ nmcli r wifi on

    - List available wifi networks

            $ nmcli d wifi list

    - Connect to access point

            $ nmcli d wifi connect '<ssid>' password '<password>'

    - Connect to a Hidden Network

            $ nmcli c add type wifi con-name '<arbitrary_name>' ifname wlan0 ssid '<ssid>'
            $ nmcli c modify '<arbitrary_name>' wifi-sec.key-mgmt wpa-psk wifi-sec.psk '<password>'
            $ nmcli c up '<arbitrary_name>'

## Miscellaneous

1. Compress file: `zip -r <archied_name>.zip <original_folder>`

1. Extract .zip file: `unzip <archied_name>.zip`

1. Get public IPv4: `dig +short myip.opendns.com @resolver1.opendns.com`

1. Setup UART for Raspberry Pi

    - Disable Login Shell over Serial

    - Enabel Serial Port Hardware

            $ sudo raspi-config
            [SELECT] 5. Interfacing Options
            [SELECT] P6 Serial

    - Disable Bluetooth and Stop Bluetooth service

            $ sudo nano /boot/config.txt
            [ACTION] xuống cuối văn bản
            [ACTION] paste "dtoverlay=pi3-disable-bt"

            $ sudo systemctl disable hciuart

        (để bật bluetooth trở lại > thay `dtoverlay=pi3-enable-bt`)

    - Reboot

            $ sudo reboot

1. Scan các mạng wi-fi lân cận: `sudo iwlist wlan0 scan`

1. Thêm thông tin cấu hình vào:

        $ sudo nano /etc/wpa_supplicant/wpa_supplicant.conf

        [ADD]
        network={
            ssid="<your_ssid>"
            psk="<your_passwork>"
            key_mgmt=WPA-PSK
        }

        [ACTION] CtrlX -> Y để lưu file

        $ sudo iwconfig wlan0 essid "ID" key "Pass"

1. Tùy chỉnh chạy trương trình khi khởi động

        $ sudo nano /etc/rc.local
        $ sudo /etc/rc.local

1. Cài đặt múi giờ

        $ sudo cp /usr/share/zoneinfo/Asia/Ho_Chi_Minh /etc/localtime

1. Chạy đoạn chương trình khi bật cửa sổ terminal

        $ sudo nano /home/pi/.bashrc
        [ADD] python3 -m pip install --upgrade pip

1. Sử dụng Camera trên Raspberry Pi3

    [Reference 1](https://www.raspberrypi.org/app/uploads/2013/07/RaspiCam-Documentation.pdf)\
    [Reference 2](https://raspberrypi.vn/thu-thuat-raspberry-pi/su-dung-camera-tren-raspberry-pi-3-2736.pi)

    - Cấu hình cho Camera

            Menu > Preferences > Raspberry Pi Configuration > Interfaces > Enable Camera > OK

    - Taking Picture

            $ raspistill -o PictureName.jpg
            $ raspistill -t 10000 -o PictureName.jpg
            $ raspistill -w 800 -h 600 -t 10000 -o /home/pi/camera/PictureName.jpg

    - Capture Video

            $ raspivid -o VideoName.mp4
            $ raspivid -t 10000 -o VideoName.mp4
            $ raspivid -w 320 -h 240 -fps 24 -t 25000 -o /home/pi/camera/VideoName.mp4

1. Remote Desktop and Raspberry Pi

        $ sudo apt-get install xrdp

1. List file: `ls`

1. Ra màn hình desktop: `cd ~/Desktop/`

1. Truy cập thư mục: `cd <folder_name>`

1. Tạo thư mục mới: `mkdir <folder_name>`

1. Edit một file <filename>.xx: `sudo nano <filename>.xx`

1. Tải file từ internet: `wget <link_file_download>`

1. Thoát chương trình: `ctrl + C`

1. Giải nén file .tgz hoặc .tar.gz: `tar -xvzf tenfile`

1. Chạy file thực thi: `./tenfile`

1. `pwd` : current directory

1. `reset`: Làm sạch Terminal

1. `nano ten_file`  : Tạo file với Nano

1. `ctrl+x` sau đó nhập `y` và `Enter` để lưu file.

1. `touch tenfile`  : Tạo nhanh file trống

1. `mkdir tenthumuc`  (make directory): Tạo thư mục

1. `cp filecu filemoi`  (copy): Sao chép file

1. `cp -r thumuccu thumucmoi`  : Sao chép thư mục

1. `mv tencu tenmoi`  (move): Đổi tên file/thư mục

1. `rm tenfile`  (remove): Xóa file

1. `rm -r tenthumuc`  : Xóa thư mục

1. `rm -r *`  : Xóa toàn bộ thư mục

1. `zip -r archive_name.zip folder_to_compress`  : Nén folder

1. `unzip archive_name.zip`  : giải nén file zip

1. `rm -rf ~/.local/share/Trash/*`  : empty trash

1. `du -Sh <file>`  : Xem kích thước file

1. `readlink -f <file>` : Lấy đường dẫn tuyệt đối của file

1. `ln -s <source.file> <softlink.file>` : softlink (or symlink)

1. `ln  <source.file> <hardlink.file>`: hardlink




## 20+ linux command for Data Science

[Reference](https://nguyenvanhieu.vn/linux-command-huu-ich-danh-cho-data-scientist/)

1. Download dữ liệu từ internet

    |Description    |Command    |               |
    |---------------|-----------|---------------|
    |check version  |`wget -v`    |`wget --version` |
    |help message|`wget -h [URL]`|`wget --help [URL]`|
    |log tất cả các message của hệ thống vào logfile|`wget -o logfile [URL]`||
    |tải trong background|`wget -b [URL]`|`wget --background [URL]`|
    |append vào logfile|`wget -a logfile [URL]`||
    ||`wget -i inputfile`|`wget -i inputfile [URL]`|
    ||`wget -t number [URL]`||
    |đặt số lần exception khi truy xuất lỗi||`wget --tries number [URL]`|
    |tiếp tục tải file nếu file có khả năng tải tiếp tục|`wget -c [URL]`||
    |khoảng thời gian s giữa các lần truy xuất, sử dụng các hậu tố #m cho phút, #h cho giờ, #d cho ngày|`wget -w number_in_seconds [URL]`||
    |recursive retrieving|`wget -r [URL]`||
    |Tải và lưu file với tên filename|`curl -o [filename] [URL...]`||
    |Tải và lưu file với tên trong URL|`curl -O [URL...]`||
    |Tiếp tục tải file đã bị dừng vì một số lý do|`curl -C - [URL...]`||
    |Đặt ngưỡng trên cho tốc độ truyền (byte)||`curl --limit-rate [value] [URL...]`|
    |tải file từ FTP server.|`curl -u <username>:<password> [FTP_URL]`||
    |upload file tới FTP server|`curl -u <username>:<password> -T <filename> <FTP_Location>`||
    |hiển thị code C tương ứng||`curl [URL...] --libcurl [filename]`|
    |sử dụng proxy để truy cập URL|`curl -x [proxy_name]:[port] [URL...]`|`curl --proxy [proxy_name]:[port] [URL...]`|
    |truyền file qua giao thức SMTP - send mails||`curl --url 'smtps://smtp.gmail.com:465' --ssl-reqd --mail-from 'example_mail@gmail.com' --mail-rcpt 'mary@gmail.com' --mail-rcpt 'eli@example.com' --use-ascii 'Luong Tan Dat' --upload-file namdotnet.txt --user 'example_mail@gmail.com:google' --insecure`|
    |tra từ điển|`curl dict:[dictionary_URL]:[word] e.g: curl dict://dict.org/d:love`||

1. Xem nội dung tập tin

    |Description|Command|
    |---|---|
    |xem n dòng đầu |`head -n [number_of_line] [filename]`|
    |xem n dòng cuối |`tail -n [number_of_line] [filename]`|
    |Đếm số từ, số dòng trong file |`cat [filename] | less`|
    |đếm số từ, số dòng, số byte dữ liệu|`wc [filename]`|
    |đếm số từ|`wc -w [filename]`|
    |đếm số line|`wc -l [filename]`|


1. Sắp xếp và xóa trùng lặp trong 1 file dữ liệu văn bản.

        $ sort [filename] [-o new_filename]
        $ sort [filename] [--output new_filename]

1. Sắp xếp theo số hoặc chữ, không có tham số output thì  xuất ra terminal

        $ sort -u [filename] [-o new_filename]
        $ sort --unique [filename] [--output new_filename]
	

1. Xóa các dòng trùng lặp

        $ sort -f [filename] [-o new_filename]
        $ sort --ignore-case [filename] [--output new_filename]

1. Sắp xếp không phân biệt chữ hoa chữ thường

        $ sort -r [filename] [-o new_filename]
        $ sort --reverse [filename] [--output new_filename]
	
1. Đếm tần suất xuất hiện của mỗi dòng text trong file.

        $ sort [filename] | uniq -c
        $ sort [filename] | uniq -c | awk '{print $2, $1}'

1. Kiểm tra, xóa dòng theo điều kiện (sử dụng Regex)

        $ grep [pattern] [filename]

    e.g:
        
        $ grep "yêu" data.txt
        $ grep "y[êế]u" data.txt
	

1. Tìm kiếm bằng regex

        $ grep -i [pattern] [filename]

    e.g:

        $ grep -i "^anh" data.txt

1. Tìm kiếm không phân biệt chữ hoa chữ thường

        $ grep [pattern] [filename] > [output]

1. Trích xuất các dòng thỏa mãn pattern

        $ grep -v [pattern] [filename] > [output]

1. Trích xuất các dòng không thỏa mãn pattern

1. Xóa dòng dài hơn, ngắn hơn x ký tự

1. Kiểm tra encoding của một file văn bản

        $ file [filename]

1. Convert giữa các kiểu encoding

        $ iconv -f [from-encoding] -t [to-encoding] [input-file] -o [output-file]
	
1. xem các encoding mà iconv hỗ trợ
        $ iconv -l
	
1. Xóa các dòng dữ liệu của file A có trong file B

        $ grep -Fvxf [lines-to-remove] [all-lines] > [output]

1. Trộn ngẫu nhiên (Shuffle) các dòng

        $ cat [file1] [file2] | shuf -o [output]
	
1. Gộp dữ liệu của nhiều file và trộn dữ liệu

        $ sort -R [filename] -o [output]
        $ sort --random-sort [filename] -o [output]
        $ sort -R [file1] [file2] -o [output]
        $ sort --random-sort [file1] [file2] -o [output]

1. Split file thành nhiều file nhỏ hơn

        $split -l [number_of_line] [bigfile] [output_dir]/[prefix]













## Code GPIO:

Cài đặt git-core: `sudo apt-get install git-core`

Thực hiện update bộ nhớ cache: `sudo apt-get update`

Tải thư viện wiringPi: `git clone git://git.drogon.net/wiringPi`

Vào thư mục vừa tải về: `cd wiringpi`

Lấy code mới nhất: `git pull origin`

Thực hiện build thư viện: `./build`

    #include<wiringPi.h>
    #include<stdio.h>

    //GPIO 17
    #define LedPin 0
    int main(void)
    {
        if(wiringPiSetup() == -1)
        {
            printf("setup wiringPi failed!");
            return 1;
        }

        pinMode(LedPin, OUTPUT);
        printf("\n\n| Blink led with period 1s |\n\n");
        while(1)
        {
            //turn LED off
            digitalWrite(LedPin, LOW);
            printf("...Led is turned on\n");
            delay(500);
            //turn LED on
            digitalWrite(LedPin, HIGH);
            printf("...Led is turned off\n");
            delay(500);
        }
        return 0;
    }

Chạy chương trình nháy led

    gcc "input" -o "output"
    gcc -o nhayLED nhayLED.c -lwiringPi
    ls -l
    sudo ./nhayLED

## Code LED 7 thanh

    #include<bcm2835.h>
    #include<stdio.h>

    #define PINA RPI_V2_GPIO_P1_11
    #define PINB RPI_V2_GPIO_P1_12
    #define PINC RPI_V2_GPIO_P1_13
    #define PIND RPI_V2_GPIO_P1_15
    #define PINE RPI_V2_GPIO_P1_16
    #define PINF RPI_V2_GPIO_P1_18
    #define PING RPI_V2_GPIO_P1_22
    #define PINH RPI_V2_GPIO_P1_29

    unsigned char numbers[10] = {0x40, 0x79, 0x24, 0x30, 0x19, 0x12, 0x02, 0x78, 0x00, 0x10};

    void setup()
    {
        bcm2835_gpio_fsel(PINA, BCM2835_GPIO_FSEL_OUTP);
        bcm2835_gpio_fsel(PINB, BCM2835_GPIO_FSEL_OUTP);
        bcm2835_gpio_fsel(PINC, BCM2835_GPIO_FSEL_OUTP);
        bcm2835_gpio_fsel(PIND, BCM2835_GPIO_FSEL_OUTP);
        bcm2835_gpio_fsel(PINE, BCM2835_GPIO_FSEL_OUTP);
        bcm2835_gpio_fsel(PINF, BCM2835_GPIO_FSEL_OUTP);
        bcm2835_gpio_fsel(PING, BCM2835_GPIO_FSEL_OUTP);
        bcm2835_gpio_fsel(PINH, BCM2835_GPIO_FSEL_OUTP);
    }

    void display(int value)
    {
        bcm2835_gpio_write(PINA, (value & 0x01));
        bcm2835_gpio_write(PINB, (value & 0x02));
        bcm2835_gpio_write(PINC, (value & 0x04));
        bcm2835_gpio_write(PIND, (value & 0x08));
        bcm2835_gpio_write(PINE, (value & 0x10));
        bcm2835_gpio_write(PINF, (value & 0x20));
        bcm2835_gpio_write(PING, (value & 0x40));
        bcm2835_gpio_write(PINH, (value & 0x80));
    }

    int main()
    {
        int i = 0;
        if(!bcm2835_init())
        return 1;
        setup();
        while(1)
        {
            display(numbers[i%10]);
            printf("Number %d\n", i);
            i++;
            bcm2835_delay(1500);
        }
        bcm2835_close();
        return 0;
    }

Build and run

    Gcc -o led7thanh led7thanh.c -l bcm2835
    Sudo ./led7thanh

## Giao tiếp với nút nhấn.

    #include<wiringPi.h>
    #include<stdio.h>

    #define button 0 /* GPIO17 */
    #define LED1 1 /* GPIO18 */
    #define LED2 4 /* GPIO23 */

    digitalWrite(LED1, HIGH);
    int main(void)
    {
        int _count;
        if(wiringPiSetup() == -1)
        {
            printf("Setup wiringPi Failed!\n");
            return -1;
        }
        pinMode(LED1, OUTPUT);
        pinMode(LED2, OUTPUT);
        pinMode(button, INPUT);
        while(1)
        {
            digitalRead(button);
            if(digitalRead(button) == HIGH)
            {
                digitalWrite(LED1, HIGH);
                digitalWrite(LED2, LOW);
            }
            else
            {
                digitalWrite(LED2, HIGH);
                digitalWrite(LED1, LOW);
            }
        }
    }

## Điều khiển GPIO bằng file hệ thống

B1. Truy vập vào thư mục gpio: `cd /sys/class/gpio`

B2. Tạo ra thư mục điều khiển gpio14: `echo 14 > export`

B3. Thiết lập chân output: `echo out > direction`

B4. Đưa chân lên mức cao (bật LED): `echo 1 > value`

B5. Đưa chân xuống mức thấp (tắt LED): `echo 0 > value`

 