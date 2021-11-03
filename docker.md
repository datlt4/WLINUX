# Docker cơ bản

Docker daemon:

- Tiến trình chạy ngầm quản lý các container

Docker client:

- Kiểm soát hầu hết các workflow của Docker
- GIao tiếp với các máy chủ Docker qua daemon

Docker Hub (Registry):

- Chứa các component Docker
- Cho phép lưu, sử dụng, tìm kiếm image

# Docker command

- `docker images`

Liệt kê tất cả các images có trong máy

- `docker search <tên_image>`

Tìm kiếm `docker images <...>`

- `docker rmi <tên_image or id>`

Xóa docker images

- `docker pull <name_image:tag>`

Tải image về `local`. Dùng khi muốn làm việc offline. Phần :tag là option, nếu để trống thì mặc định download bản latest.

- `docker save[OPTION] IMAGE [IMAGE...]`

Sao lưu image 1 bản backup lên local máy, thuận tiện vận chuyển image đến khách hàng

```
docker save -o tên-backup-image.tar.gz tên_image1:tag tên_image2 ...
```

- `docker load [OPTION]`

Xuất ra image đã lưu

- `docker load -i tên-backup-image.tar.gz`
```
-i: input
```

- `docker run [OPTION] <tên_image> -it -p <host_port>:<container_port> -v <folder_local>:<folder_container> -- memory <total-memory-limit> --cpu-share=<limit> --cpu-period=<period-limit> --cpu-quota=<quota-limit> <image> <command>`

Tạo Docker container từ image <...>
Nếu image chưa tồn tại trong máy, tự động tải về

|Options|Description|
|---|---|
|--name|đặt tên cho container|
|-it|sẽ cung cấp một phiên tương tác với `pseudo-TTY`, cung cấp shell của container ngay lập tức|
|-p|mở port container ra ngoài|
|-d|bật chế độ chạy background|
|-v (volume)|thư mục|
|-rm|container tự động xóa sau khi khi tiến trình container kết thúc|

```
docker run -it <tên_image>
docker run --name <tên_container>
docker run –cpu-share=20 –cpu-period=40000 –cpu-quota=20000
```

- `docker attach <id>`

Truy cập container đang chạy thông qua ID hoặc tên. Có thể truy cập và cùng một container từ nhiều nơi tại cùng một thời điểm. `Ctrl+P` / `Ctrl+Q` để ra khỏi container, 

`docker run -ti`: vẫn để tiến trình chạy.

- `docker exec <id>`

Khởi tạo một process khác bên trong container đã có. Không thể thêm port, volume,...

- `docker create <image>`

Tạo ra 1 container với các config tương tự `docker run`. Container không được chạy ngay từ đầu. Dùng `docker start` để chạy container

- `docker start <id or tên_ container>`

Khởi động lại container đã dừng

- `docker stop <id or tên_container>`

Dừng container đang chạy

- `docker ps`

Liệt kê các container đang chạy

`docker ps -a`: Liệt kê tất cả các container tồn tại

`docker ps -l`: Container chạy gần đây nhất

- `docker rm <id or tên_container>`

Xóa container
`docker ps -a -q` : xóa tất cả container

- `docker commit [OPTION] <id_container> <REPOSITORY[:TAG]]>`

Tạo image với trạng thái hiện tại của container <id>

`docker cp`
 
Copy dữ liệu từ container tới local machine và ngược lại. Áp dụng cho cả stopped và running container

Đường dẫn relative `sharp_bell:/tmp/example.txt`, `sharp_bell:tmp/example.txt`
Copy file từ `local machine` vào `container`

```
docker cp example.txt sharp_bell:/root/example.txt
```

- `docker inspect <id>`

Kiểm tra cấu hình container

- `Tra IP container:`

docker inspect <id> | grep IPAddress

# `Dockerfile`

Mỗi dòng  lấy image tạo ra từ dòng trước đó để tạo một image mới .Không chỉnh sửa trạng  thái của dòng trước đó .Phần code chỉnh sửa nên đặt  ở cuối `Dockerfile `. Các tiến  trình chạy tên một dòng sẽ không chạy  ở  dòng  tiếp theo . Các biến môi trường được đặt sẽ giữ lại ở dòng tiếp theo . Mỗi dòng trong dockerfile đều gọi tới `docker run `.
```
docker build [OPTION] PATH |URL | - 
```	

- Build image từ dockerfile 

```
docker build -t  demo:1.0 
```
 
- `[ERROR] Got permission denied while trying to connect to the Docker daemon socket at unix:///var/run/docker.sock`

```
sudo newgrp docker
sudo chmod 666 /var/run/docker.sock
sudo usermod -aG docker ${USER}
 ```
 
- Clean

```
docker container prune -f
docker image prune -f
docker volume prune -f
```

[ ] https://nguyenvanhieu.vn/docker-la-gi/?medium=ltkk 

# Dockerfile, Images & Containers

## Dockerfile 

- Một script chứa tất cả các câu lệnh command line để build một Docker image. 
- `docker build` cho phép tự động build một image từ Dockerfile cho trước 

## Images 

- Docker image có thể coi như là các template cho các Docker container. 
- Từ các template này, có thể tạo ra các Docker container giống nhau. 
- Đây là các file chỉ đọc. 
- `docker run` giúp tạo các Docker container. 

## Containers 

Phiên bản executable của docker image. 
Giữ toàn bộ các package cần để chạy ứng dụng. 

## Tạo Docker Image của riêng mình. 

[Reference] https://nguyenvanhieu.vn/docker-la-gi/?medium=ltkk#tao-docker-image-cua-rieng-ban 

- Tạo thư mục để làm việc 

```
mkdir news-crawler 
cd news-crawler/ 
```

- Tạo file Dockerfile 

```
FROM ubuntu:18.04 
MAINTAINER laptrinhkhongkho 

# Cài đặt git và python==3.6 
RUN apt-get update && apt-get install -y software-properties-common && add-apt-repository ppa:deadsnakes/ppa &&  apt-get update && apt-get install -y python3.6 python3.6-dev python3-pip && apt-get install -y git 
RUN ln -sfn /usr/bin/python3.6 /usr/bin/python3 && ln -sfn /usr/bin/python3 /usr/bin/python && ln -sfn /usr/bin/pip3 /usr/bin/pip 

# Clone git repo 
RUN git clone https://github.com/nguyenvanhieuvn/news-crawler.git app 
WORKDIR /app 
RUN pip install -r requirements.txt 
EXPOSE 5001 
ENTRYPOINT [ "python" ] 
CMD [ "app.py" ] 
```

- Build dockerfile để tạo Docker image 

```
sudo docker build --tag news-crawler . 
```

- Tạo container từ Docker image đã build 

```
sudo docker run --name news-crawler -p 9000:5001 news-crawler 
```

- Kiếm tra Docker image đã có trong danh sách 

```
sudo docker image ls 
```
