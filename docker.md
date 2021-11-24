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

# [Docker Compose](https://github.com/docker/awesome-compose)

<details>
  <summary>Awesome Docker compose example!</summary>

- `angular`

```dockerfile
services:
  web:
    build: angular
    ports:
      - 4200:4200
    volumes:
      - ./angular:/project
      - /project/node_modules
```

- `apache-php`

```dockerfile
services:
  web:
    build: app
    ports:
      - '80:80'
    volumes:
      - ./app:/var/www/html/
```

- `aspnet-mssql`

```dockerfile
services:
  web:
    build: app/aspnetapp
    ports:
      - 80:80
  db:
    environment:
      ACCEPT_EULA: "Y"
      SA_PASSWORD: example_123
    # mssql server image isn't available for arm64 architecture, so we use azure-sql instead
    image: mcr.microsoft.com/azure-sql-edge:1.0.4
    # If you really want to use MS SQL Server, uncomment the following line
    # image: mcr.microsoft.com/mssql/server
    restart: always
    healthcheck:
        test: ["CMD-SHELL", "/opt/mssql-tools/bin/sqlcmd -S localhost -U sa -P example_123 -Q 'SELECT 1' || exit 1"]
        interval: 10s
        retries: 10
        start_period: 10s
        timeout: 3s
 
```

- `django`

```dockerfile
services:
  web:
    build: app
    ports:
      - '8000:8000'
```

- `elasticsearch-logstash-kibana`

```dockerfile
services:
  elasticsearch:
    image: elasticsearch:7.14.2
    container_name: es
    environment:
      discovery.type: single-node
      ES_JAVA_OPTS: "-Xms512m -Xmx512m"
    ports:
      - "9200:9200"
      - "9300:9300"
    healthcheck:
      test: ["CMD-SHELL", "curl --silent --fail localhost:9200/_cluster/health || exit 1"]
      interval: 10s
      timeout: 10s
      retries: 3
    networks:
      - elastic
  logstash:
    image: logstash:7.14.2
    container_name: log
    environment:
      discovery.seed_hosts: logstash
      LS_JAVA_OPTS: "-Xms512m -Xmx512m"
    volumes:
      - ./logstash/pipeline/logstash-nginx.config:/usr/share/logstash/pipeline/logstash-nginx.config
      - ./logstash/nginx.log:/home/nginx.log
    ports:
      - "5000:5000/tcp"
      - "5000:5000/udp"
      - "5044:5044"
      - "9600:9600"
    depends_on:
      - elasticsearch
    networks:
      - elastic
    command: logstash -f /usr/share/logstash/pipeline/logstash-nginx.config
  kibana:
    image: kibana:7.14.2
    container_name: kib
    ports:
      - "5601:5601"
    depends_on:
      - elasticsearch
    networks:
      - elastic
networks:
  elastic:
    driver: bridge
```

- `fastapi`

```dockerfile
services:
  api:
    build: .
    container_name: fastapi-application
    environment:
      PORT: 8000
    ports:
      - '8000:8000'
    restart: "no"
```

- `flask`

```dockerfile
services:
  web:
    build: app
    ports:
      - '5000:5000'
```

- `gitea-postgres`

```dockerfile
services:
  gitea:
    image: gitea/gitea:latest
    environment:
      - DB_TYPE=postgres
      - DB_HOST=db:5432
      - DB_NAME=gitea
      - DB_USER=gitea
      - DB_PASSWD=gitea
    restart: always
    volumes:
      - git_data:/data
    ports:
      - 3000:3000
  db:
    image: postgres:alpine
    environment:
      - POSTGRES_USER=gitea
      - POSTGRES_PASSWORD=gitea
      - POSTGRES_DB=gitea
    restart: always
    volumes:
      - db_data:/var/lib/postgresql/data
    expose:
      - 5432
volumes:
  db_data:
  git_data:
```

- `minecraft`

```dockerfile
services:
 minecraft:
   image: itzg/minecraft-server
   ports:
     - "25565:25565"
   environment:
     EULA: "TRUE"
   deploy:
     resources:
       limits:
         memory: 1.5G
   volumes:
     - "~/minecraft_data:/data"
```

- `nextcloud-postgres`

```dockerfile
services:
  nc:
    image: nextcloud:apache
    environment:
      - POSTGRES_HOST=db
      - POSTGRES_PASSWORD=nextcloud
      - POSTGRES_DB=nextcloud
      - POSTGRES_USER=nextcloud
    ports:
      - 80:80
    restart: always
    volumes:
      - nc_data:/var/www/html
  db:
    image: postgres:alpine
    environment:
      - POSTGRES_PASSWORD=nextcloud
      - POSTGRES_DB=nextcloud
      - POSTGRES_USER=nextcloud
    restart: always
    volumes:
      - db_data:/var/lib/postgresql/data
    expose:
      - 5432
volumes:
  db_data:
  nc_data:
```

- `nextcloud-redis-mariadb`

```dockerfile
services:
  nc:
    image: nextcloud:apache
    restart: always
    ports:
      - 80:80
    volumes:
      - nc_data:/var/www/html
    networks:
      - redisnet
      - dbnet
    environment:
      - REDIS_HOST=redis
      - MYSQL_HOST=db
      - MYSQL_DATABASE=nextcloud
      - MYSQL_USER=nextcloud
      - MYSQL_PASSWORD=nextcloud
  redis:
    image: redis:alpine
    restart: always
    networks:
      - redisnet
    expose:
      - 6379
  db:
    image: mariadb:10.5
    command: --transaction-isolation=READ-COMMITTED --binlog-format=ROW
    restart: always
    volumes:
      - db_data:/var/lib/mysql
    networks:
      - dbnet
    environment:
      - MYSQL_DATABASE=nextcloud
      - MYSQL_USER=nextcloud
      - MYSQL_ROOT_PASSWORD=nextcloud
      - MYSQL_PASSWORD=nextcloud
    expose:
      - 3306
volumes:
  db_data:
  nc_data:
networks:
  dbnet:
  redisnet:
```

- `nginx-aspnet-mysql`

```dockerfile
services:
  backend:
    build: backend
    restart: always
    secrets:
      - db-password
    depends_on:
      - db
    environment:
      - ASPNETCORE_URLS=http://+:8000
    # depends_on:
    #   db:
    #     condition: service_healthy
  db:
    # We use a mariadb image which supports both amd64 & arm64 architecture
    image: mariadb:10.6.4-focal
    # If you really want to use MySQL, uncomment the following line
    # image: mysql:8.0.27
    command: '--default-authentication-plugin=mysql_native_password'
    restart: always
    healthcheck:
      test: ["CMD", "mysqladmin", "ping", "-h", "127.0.0.1", "--silent"]
      interval: 3s
      retries: 5
      start_period: 30s
    secrets:
      - db-password
    volumes:
      - db-data:/var/lib/mysql
    environment:
      - MYSQL_DATABASE=example
      - MYSQL_ROOT_PASSWORD_FILE=/run/secrets/db-password
  proxy:
    build: proxy
    ports:
      - 80:80
    depends_on:
      - backend
volumes:
  db-data:
secrets:
  db-password:
    file: db/password.txt```

- `nginx-flask-mongo`

```dockerfile
services:
  web:
    image: nginx
    volumes:
      - ./nginx/nginx.conf:/tmp/nginx.conf
    environment:
      - FLASK_SERVER_ADDR=backend:9091
    command: /bin/bash -c "envsubst < /tmp/nginx.conf > /etc/nginx/conf.d/default.conf && nginx -g 'daemon off;'"
    ports:
      - 80:80
    depends_on:
      - backend
  backend:
    build: flask
    environment:
      - FLASK_SERVER_PORT=9091
    volumes:
      - ./flask:/src
    depends_on:
      -  mongo
  mongo:
    image: mongo
```

- `nginx-flask-mysql`

```dockerfile
services:
  db:
    # We use a mariadb image which supports both amd64 & arm64 architecture
    image: mariadb:10.6.4-focal
    # If you really want to use MySQL, uncomment the following line
    # image: mysql:8.0.27
    command: '--default-authentication-plugin=mysql_native_password'
    restart: always
    healthcheck:
      test: ["CMD", "mysqladmin", "ping", "-h", "127.0.0.1", "--silent"]
      interval: 3s
      retries: 5
      start_period: 30s
    secrets:
      - db-password
    volumes:
      - db-data:/var/lib/mysql
    networks:
      - backnet
    environment:
      - MYSQL_DATABASE=example
      - MYSQL_ROOT_PASSWORD_FILE=/run/secrets/db-password
    expose:
      - 3306
      - 33060
  backend:
    build: backend
    restart: always
    secrets:
      - db-password
    ports:
      - 5000:5000
    networks:
      - backnet
      - frontnet
    depends_on:
      db:
        condition: service_healthy
  proxy:
    build: proxy
    restart: always
    ports:
      - 80:80
    depends_on:
      - backend
    networks:
      - frontnet
volumes:
  db-data:
secrets:
  db-password:
    file: db/password.txt
networks:
  backnet:
  frontnet:
```

- `nginx-golang`

```dockerfile
services:
  frontend:
    build: frontend
    ports:
      - 80:80
    depends_on:
      - backend
  backend:
    build: backend
```

- `nginx-golang-mysql`

```dockerfile
services:
  backend:
    build: backend
    secrets:
      - db-password
    depends_on:
      db:
        condition: service_healthy
  db:
    # We use a mariadb image which supports both amd64 & arm64 architecture
    image: mariadb:10.6.4-focal
    # If you really want to use MySQL, uncomment the following line
    # image: mysql:8.0.27
    command: '--default-authentication-plugin=mysql_native_password'
    restart: always
    healthcheck:
      test: ["CMD", "mysqladmin", "ping", "-h", "127.0.0.1", "--silent"]
      interval: 3s
      retries: 5
      start_period: 30s
    secrets:
      - db-password
    volumes:
      - db-data:/var/lib/mysql
    environment:
      - MYSQL_DATABASE=example
      - MYSQL_ROOT_PASSWORD_FILE=/run/secrets/db-password
    expose:
      - 3306
  proxy:
    build: proxy
    ports:
      - 80:80
    depends_on:
      - backend
volumes:
  db-data:
secrets:
  db-password:
    file: db/password.txt
```

- `nginx-golang-postgres`

```dockerfile
services:
  backend:
    build: backend
    secrets:
      - db-password
    depends_on:
      - db
  db:
    image: postgres
    restart: always
    secrets:
      - db-password
    volumes:
      - db-data:/var/lib/postgresql/data
    environment:
      - POSTGRES_DB=example
      - POSTGRES_PASSWORD_FILE=/run/secrets/db-password
    expose:
      - 5432

  proxy:
    build: proxy
    ports:
      - 80:80
    depends_on:
      - backend
volumes:
  db-data:
secrets:
  db-password:
    file: db/password.txt
```

- `nginx-wsgi-flask`

```dockerfile
services:
  nginx-proxy:
    build: nginx
    restart: always
    volumes:
      - ./nginx/default.conf:/tmp/default.conf
    environment:
      - FLASK_SERVER_ADDR=flask-app:8000
    ports:
      - "80:80"
    depends_on:
      - flask-app
    healthcheck:
      test: ["CMD-SHELL", "curl --silent --fail localhost:80/health-check || exit 1"]
      interval: 10s
      timeout: 10s
      retries: 3
    command: /app/start.sh
  flask-app:
    build: flask
    restart: always
    ports:
      - '8000:8000'
    healthcheck:
      test: ["CMD-SHELL", "curl --silent --fail localhost:8000/flask-health-check || exit 1"]
      interval: 10s
      timeout: 10s
      retries: 3
    command: gunicorn -w 3 -t 60 -b 0.0.0.0:8000 app:app
```

- `prometheus-grafana`

```dockerfile
services:
  prometheus:
    image: prom/prometheus
    container_name: prometheus
    command:
      - '--config.file=/etc/prometheus/prometheus.yml'
    ports:
      - 9090:9090
    restart: unless-stopped
    volumes:
      - ./prometheus:/etc/prometheus
      - prom_data:/prometheus
  grafana:
    image: grafana/grafana
    container_name: grafana
    ports:
      - 3000:3000
    restart: unless-stopped
    environment:
      - GF_SECURITY_ADMIN_USER=admin
      - GF_SECURITY_ADMIN_PASSWORD=grafana
    volumes:
      - ./grafana:/etc/grafana/provisioning/datasources
volumes:
  prom_data:
```

- `react-express-mongodb`

```dockerfile
services:
  frontend:
    build: frontend
    ports:
      - 3000:3000
    stdin_open: true
    volumes:
      - ./frontend:/usr/src/app
      - /usr/src/app/node_modules
    container_name: frontend
    restart: always
    networks:
      - react-express
    depends_on:
      - backend
  backend:
    container_name: backend
    restart: always
    build: backend
    volumes:
      - ./backend:/usr/src/app
      - /usr/src/app/node_modules
    depends_on:
      - mongo
    networks:
      - express-mongo
      - react-express
    expose:
      - 3000
  mongo:
    container_name: mongo
    restart: always
    image: mongo:4.2.0
    volumes:
      - ./data:/data/db
    networks:
      - express-mongo
    expose:
      - 27017
networks:
  react-express:
  express-mongo:
```

- `react-express-mysql`

```dockerfile
services:
  backend:
    build:
      args:
      - NODE_ENV=development
      context: backend
    command: npm run start-watch
    environment:
      - DATABASE_DB=example
      - DATABASE_USER=root
      - DATABASE_PASSWORD=/run/secrets/db-password
      - DATABASE_HOST=db
      - NODE_ENV=development
    ports:
      - 80:80
      - 9229:9229
      - 9230:9230
    secrets:
      - db-password
    volumes:
      - ./backend/src:/code/src:ro
      - ./backend/package.json:/code/package.json
      - ./backend/package-lock.json:/code/package-lock.json
      - back-notused:/opt/app/node_modules
    networks:
      - public
      - private
    depends_on:
      - db
  db:
    # We use a mariadb image which supports both amd64 & arm64 architecture
    image: mariadb:10.6.4-focal
    # If you really want to use MySQL, uncomment the following line
    # image: mysql:8.0.27
    command: '--default-authentication-plugin=mysql_native_password'
    restart: always
    secrets:
      - db-password
    volumes:
      - db-data:/var/lib/mysql
    networks:
      - private
    environment:
      - MYSQL_DATABASE=example
      - MYSQL_ROOT_PASSWORD_FILE=/run/secrets/db-password
  frontend:
    build:
      context: frontend
      target: development
    ports:
      - 3000:3000
    volumes:
      - ./frontend/src:/code/src
      - /code/node_modules
    networks:
      - public
    depends_on:
      - backend
networks:
  public:
  private:
volumes:
  back-notused:
  db-data:
secrets:
  db-password:
    file: db/password.txt
```

- `react-java-mysql`

```dockerfile
services:
  backend:
    build: backend
    restart: always
    secrets:
      - db-password
    environment:
      MYSQL_HOST: db
    networks:
      - react-spring
      - spring-mysql
    depends_on:
      db:
        condition: service_healthy
  db:
    # We use a mariadb image which supports both amd64 & arm64 architecture
    image: mariadb:10.6.4-focal
    # If you really want to use MySQL, uncomment the following line
    # image: mysql:8.0.19
    environment:
      - MYSQL_DATABASE=example
      - MYSQL_ROOT_PASSWORD_FILE=/run/secrets/db-password
    restart: always
    healthcheck:
      test: ["CMD", "mysqladmin", "ping", "-h", "127.0.0.1", "--silent"]
      interval: 3s
      retries: 5
      start_period: 30s
    secrets:
      - db-password
    volumes:
      - db-data:/var/lib/mysql
    networks:
      - spring-mysql
  frontend:
    build:
      context: frontend
      target: development
    ports:
      - 3000:3000
    volumes:
      - ./frontend/src:/code/src
      - /project/node_modules
    networks:
      - react-spring
    depends_on:
      - backend
    expose:
      - 3306
      - 33060
volumes:
  db-data: {}
secrets:
  db-password:
    file: db/password.txt
networks:
  react-spring: {}
  spring-mysql: {}
```

- `react-nginx`

```dockerfile
version: "3.7"
services:
  frontend:
    build:
      context: .
    container_name: frontend
    ports:
      - "80:80"
```

- `react-rust-postgres`

```dockerfile
services:
  frontend:
    build:
      context: frontend
      target: development
    networks:
      - client-side
    ports:
      - 3000:3000
    volumes:
      - ./frontend/src:/code/src:ro
  backend:
    build:
      context: backend
      target: development
    environment:
      - ADDRESS=0.0.0.0:8000
      - RUST_LOG=debug
      - PG_DBNAME=postgres
      - PG_HOST=db
      - PG_USER=postgres
      - PG_PASSWORD=mysecretpassword
    networks:
      - client-side
      - server-side
    volumes:
      - ./backend/src:/code/src
      - backend-cache:/code/target
    depends_on:
      - db
  db:
    image: postgres:12-alpine
    restart: always
    environment:
      - POSTGRES_PASSWORD=mysecretpassword
    networks:
      - server-side
    ports:
      - 5432:5432
    volumes:
      - db-data:/var/lib/postgresql/data
networks:
  client-side: {}
  server-side: {}
volumes:
  backend-cache: {}
  db-data: {}
```

- `sparkjava`

```dockerfile
services:
  sparkjava:
    build: sparkjava
    ports:
      - 8080:8080
```

- `sparkjava-mysql`

```dockerfile
services:
  backend:
    build: backend
    ports:
      - 8080:8080
    secrets:
      - db-password
  db:
    # We use a mariadb image which supports both amd64 & arm64 architecture
    image: mariadb:10.6.4-focal
    # If you really want to use MySQL, uncomment the following line
    # image: mysql:8.0.27
    restart: always
    secrets:
      - db-password
    volumes:
      - db-data:/var/lib/mysql
    environment:
      - MYSQL_DATABASE=example
      - MYSQL_ROOT_PASSWORD_FILE=/run/secrets/db-password
    expose:
      - 3306
      - 33060
volumes:
  db-data:
secrets:
  db-password:
    file: db/password.txt
```

- `spring-postgres`

```dockerfile
services:
  backend:
    build: backend
    ports:
      - 8080:8080
    environment:
      - POSTGRES_DB=example
    networks:
      - spring-postgres
  db:
    image: postgres
    restart: always
    secrets:
      - db-password
    volumes:
      - db-data:/var/lib/postgresql/data
    networks:
      - spring-postgres
    environment:
      - POSTGRES_DB=example
      - POSTGRES_PASSWORD_FILE=/run/secrets/db-password
    expose:
      - 5432
volumes:
  db-data:
secrets:
  db-password:
    file: db/password.txt
networks:
  spring-postgres:
```

- `traefik-golang`

```dockerfile
services:
  frontend:
    image: traefik:2.2
    command: --providers.docker --entrypoints.web.address=:80 --providers.docker.exposedbydefault=false
    ports:
      # The HTTP port
      - "80:80"
    volumes:
      # So that Traefik can listen to the Docker events
      - /var/run/docker.sock:/var/run/docker.sock
    depends_on:
      - backend
  backend:
    build: backend
    labels:
      - "traefik.enable=true"
      - "traefik.http.routers.go.rule=Path(`/`)"
      - "traefik.http.services.go.loadbalancer.server.port=80"
```

- `vuejs`

```dockerfile
services:
  web:
    build: vuejs
    ports:
      - 8080:8080
    volumes:
      - ./vuejs:/project
      - /project/node_modules
```

- `wordpress-mysql`

```dockerfile
services:
  db:
    # We use a mariadb image which supports both amd64 & arm64 architecture
    image: mariadb:10.6.4-focal
    # If you really want to use MySQL, uncomment the following line
    # image: mysql:8.0.27
    command: '--default-authentication-plugin=mysql_native_password'
    volumes:
      - db_data:/var/lib/mysql
    restart: always
    environment:
      - MYSQL_ROOT_PASSWORD=somewordpress
      - MYSQL_DATABASE=wordpress
      - MYSQL_USER=wordpress
      - MYSQL_PASSWORD=wordpress
    expose:
      - 3306
      - 33060
  wordpress:
    image: wordpress:latest
    ports:
      - 80:80
    restart: always
    environment:
      - WORDPRESS_DB_HOST=db
      - WORDPRESS_DB_USER=wordpress
      - WORDPRESS_DB_PASSWORD=wordpress
      - WORDPRESS_DB_NAME=wordpress
volumes:
  db_data:
```
</details>
 
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
