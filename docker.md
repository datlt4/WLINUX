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

# `Docker Volume`

- `Volumes`: are used to persist data, Usually use them for Databases.

- Inspect container

```bash
docker container inspect <Container>
```

- List volumes

```bash
docker volume ls
```

- Create a volume

```bash
docker volume create <new-volume-volume>
```
 
- Link the new volume created

```
docker container run -d -v <new-volume-volume>:</path/to/mount> --name <Name-container> <Image-name>
```

# Networks in Docker

- If you want to connect two or more containers, so that they can communicate with each other, they have to share the same `network`.

## Connecting two containers on the same network

- Create the network

```
docker network create <network-name>
```

- List the networks

```
docker network ls
```
- Start container and link it to new network

```
docker container run -d --rm --network <network-name> --name c1 <image1>
docker container run -d --rm --network <network-name> --name c2 <image2>
```

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
sudo groupadd docker
sudo usermod -aG docker ${USER}
mkdir -p ${HOME}/.docker
sudo chown "$USER":"$USER" ${HOME}/.docker -R
sudo chmod g+rwx "${HOME}/.docker" -R
sudo chmod 666 /var/run/docker.sock
 ```
 
- Clean

```
docker container prune -f
docker image prune -f
docker volume prune -f
```

# [Dockerfile, Images & Containers](https://nguyenvanhieu.vn/docker-la-gi/?medium=ltkk )

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

# Dockerfile

1. `FROM`

Usage:

```
FROM <image>
FROM <image>:<tag>
FROM <image>@<digest>
```

Information:

- `FROM` must be the first non-comment instruction in the Dockerfile.

2. `MAINTAINER`

Usage:

```
MAINTAINER <name>
```

- The `MAINTAINER` instruction allows you to set the Author field of the generated images.

3. `RUN`

Usage:

```
RUN <command> (shell form, the command is run in a shell, which by default is /bin/sh -c on Linux or cmd /S /C on Windows)
RUN ["<executable>", "<param1>", "<param2>"] (exec form)
```

Information:

- The exec form makes it possible to avoid shell string munging, and to `RUN` commands using a base image that does not contain the specified shell executable.


4. `LABEL`

Usage:

```
LABEL <key>=<value> [<key>=<value> ...]
```

Information:

- The `LABEL` instruction adds metadata to an image.

5. `ENV`

Usage:

```
ENV <key> <value>
ENV <key>=<value> [<key>=<value> ...]
```

Information:

- The `ENV` instruction sets the environment variable <key> to the value <value>.

6. `ARG`

Usage:

```
ARG <name>[=<default value>]
```

Information:

Defines a variable that users can pass at build-time to the builder with the docker build command using the --build-arg <varname>=<value> flag.

7. `ADD`

Usage:

```
ADD <src> [<src> ...] <dest>
ADD ["<src>", ... "<dest>"] (this form is required for paths containing whitespace)
```

Information:

- Copies new files, directories, or remote file URLs from <src> and adds them to the filesystem of the image at the path <dest>.

8. `COPY`

Usage:

```
COPY <src> [<src> ...] <dest>
COPY ["<src>", ... "<dest>"] (this form is required for paths containing whitespace)
```

Information:

- Copies new files or directories from <src> and adds them to the filesystem of the image at the path <dest>.

9. `VOLUME`

Usage:

```
VOLUME ["<path>", ...]
VOLUME <path> [<path> ...]
```

- Creates a mount point with the specified name and marks it as holding externally mounted volumes from native host or other containers.

10. `USER`

Usage:

```
USER <username | UID>
```

- The `USER` instruction sets the user name or UID to use when running the image and for any `RUN`, `CMD` and `ENTRYPOINT` instructions that follow it in the Dockerfile.

11. `WORKDIR`

Usage:

```
WORKDIR </path/to/workdir>
```

Information:

- Sets the working directory for any `RUN`, `CMD`, `ENTRYPOINT`, `COPY`, and `ADD` instructions that follow it.
- It can be used multiple times in the one Dockerfile. If a relative path is provided, it will be relative to the path of the previous `WORKDIR` instruction.

12. `ONBUILD`

Usage:

```
ONBUILD <Dockerfile INSTRUCTION>
```

Information:

- Adds to the image a trigger instruction to be executed at a later time, when the image is used as the base for another build. The trigger will be executed in the context of the downstream build, as if it had been inserted immediately after the `FROM` instruction in the downstream Dockerfile.
- Any build instruction can be registered as a trigger.
- Triggers are inherited by the "child" build only. In other words, they are not inherited by "grand-children" builds.
- The `ONBUILD` instruction may not trigger `FROM`, `MAINTAINER`, or `ONBUILD` instructions.

13. `CMD`

Usage:

```
CMD ["<executable>","<param1>","<param2>"] (exec form, this is the preferred form)
CMD ["<param1>","<param2>"] (as default parameters to ENTRYPOINT)
CMD <command> <param1> <param2> (shell form)
```

Information:

- The main purpose of a `CMD` is to provide defaults for an executing container. These defaults can include an executable, or they can omit the executable, in which case you must specify an `ENTRYPOINT` instruction as well.
- There can only be one `CMD` instruction in a Dockerfile. If you list more than one `CMD` then only the last `CMD` will take effect.
- If `CMD` is used to provide default arguments for the `ENTRYPOINT` instruction, both the `CMD` and `ENTRYPOINT` instructions should be specified with the JSON array format.
- If the user specifies arguments to docker run then they will override the default specified in `CMD`.
- Normal shell processing does not occur when using the exec form. For example, `CMD ["echo", "$HOME"]` will not do variable substitution on `$HOME`.

14. `ENTRYPOINT`

Usage:

```
ENTRYPOINT ["<executable>", "<param1>", "<param2>"] (exec form, preferred)
ENTRYPOINT <command> <param1> <param2> (shell form)
```

Information:

- Allows you to configure a container that will run as an executable.
- Command line arguments to docker run <image> will be appended after all elements in an exec form `ENTRYPOINT` and will override all elements specified using `CMD`.
- The shell form prevents any `CMD` or run command line arguments from being used, but the `ENTRYPOINT` will start via the shell. This means the executable will not be PID 1 nor will it receive UNIX signals. Prepend exec to get around this drawback.
- Only the last `ENTRYPOINT` instruction in the Dockerfile will have an effect.

15. `STOPSIGNAL`

Usage:

```
STOPSIGNAL <signal>
```

- The `STOPSIGNAL` instruction sets the system call signal that will be sent to the container to exit. This signal can be a valid unsigned number that matches a position in the kernel’s syscall table, for instance 9, or a signal name in the format `SIGNAME`, for instance `SIGKILL`.

16. `HEALTHCHECK`

Usage:

```
HEALTHCHECK [<options>] CMD <command> (check container health by running a command inside the container)
HEALTHCHECK NONE (disable any healthcheck inherited from the base image)
```

Information:

- Tells Docker how to test a container to check that it is still working
- Whenever a health check passes, it becomes healthy. After a certain number of consecutive failures, it becomes unhealthy.
