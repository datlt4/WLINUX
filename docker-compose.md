
# [Docker Compose](https://github.com/docker/awesome-compose)

## Install Compose on Windows and Mac

Docker Desktop for Mac/Windows includes Compose along with other Docker apps, so Mac/Windows users do not need to install Compose separately.

## Install Compose on Linux

1. Method `1`

```bash
sudo curl -L "https://github.com/docker/compose/releases/download/1.29.2/docker-compose-$(uname -s)-$(uname -m)" -o /usr/local/bin/docker-compose
sudo chmod +x /usr/local/bin/docker-compose
sudo ln -s /usr/local/bin/docker-compose /usr/bin/docker-compose
docker-compose --version
```

2. Method `2`

```bash
sudo apt install docker-compose -y
docker-compose --version
```

3. For `ARM64`

```bash
sudo apt-get update -y
sudo apt-get install curl python3-pip libffi-dev python-openssl libssl-dev zlib1g-dev gcc g++ make -y
sudo snap install rustup --classic
sudo apt install rustc
sudo python3 -m pip install docker-compose
sudo docker-compose --version
```

## Uninstall Compose on Linux

```bash
sudo rm /usr/local/bin/docker-compose
```

## The YAML Configuration Explained

- Docker Compose sẽ sử dụng các rules được khai báo trong `docker-compose.yml`.

- Thường thì trong file `docker-compose.yml`, ta cần khai báo version, ít nhất 1 `service`, và tùy chọn `volumes` và `networks`.

<details>
  <summary>EXAMPLE!</summary>

```dockerfile
version: "3.7"

services:
  m-service-01:
    image: ubuntu:latest
    container_name: container-01
    healthcheck:
      test: ["CMD-SHELL", "curl --silent --fail localhost:9200/_cluster/health || exit 1"]
      interval: 10s
      retries: 10
      start_period: 10s
      timeout: 3s
    restart: "no"
    stdin_open: true
    ports:
      - "80:80"
    networks:
      - m-network-01

  m-service-02:
    image: alpine:latest
    container_name: container-02
    ports:
      - "8080:3000"
    volumes:
      - m-volume-01:/my-volumes/m-volume
      - /tmp:/my-volumes/host-volume
      - /home:/my-volumes/readonly-host-volume:ro
    networks:
      - m-network-02

  m-service-03:
    build:
      context: ContextPath/ # ./
      dockerfile: Dockerfile
    image: image-03
    container_name: container-03
    restart: unless-stopped
    depends_on:
      - m-service-04
    volumes:
      - m-volume-01:/my-volumes/database
    ports:
      - "8081:3000"
      - "81:80"
    deploy:
      resources:
        limits:
          memory: 1.5G

  m-service-04:
    build: https://github.com/my-company/my-project.git
    image: image-04
    container_name: container-04
    environment:
      ACCEPT_EULA: "Y"
      SA_PASSWORD: example_123
    restart: always
    depends_on:
      m-service-04:
        condition: service_healthy
    secrets:
      - db-password
    expose:
      - "80"
    networks:
      - m-network-02
      - m-network-01
    deploy:
      mode: replicated
      replicas: 6
      resources:
        limits:
          cpus: '0.50'
          memory: 50M
        reservations:
          cpus: '0.25'
          memory: 20M

  m-service-05:
    image: "postgres:${POSTGRES_VERSION}"
    container_name: flask-app
    restart: always
    ports:
      - '8000:8000'
    healthcheck:
      test: ["CMD-SHELL", "curl --silent --fail localhost:8000/flask-health-check || exit 1"]
      interval: 10s
      timeout: 10s
      retries: 3
    command: gunicorn -w 3 -t 60 -b 0.0.0.0:8000 app:app

  db:
    # We use a mariadb image which supports both amd64 & arm64 architecture
    image: mariadb:10.6.4-$(lsb_release -cs)"
    # If you really want to use MySQL, uncomment the following line
    # image: mysql:8.0.27
    command: '--default-authentication-plugin=mysql_native_password'
    restart: always
    healthcheck:
      test:
        [
          "CMD",
          "mysqladmin",
          "ping",
          "-h",
          "127.0.0.1",
          "--silent"
        ]
      interval: 3s
      retries: 5
      start_period: 30s
    secrets:
      - db-password
    volumes:
      - db-data:/var/lib/mysql
      - /var/run/docker.sock:/var/run/docker.sock
    environment:
      - ENV-01: "${VAR}"
      - ENV-02: "${USER}"
      - MYSQL_DATABASE=example
      - MYSQL_ROOT_PASSWORD_FILE=/run/secrets/db-password
    expose:
      - 3306
    proxy:
      build: proxy
      ports:
        - 81:80
      depends_on:
        - m-service-02
    labels:
      - "traefik.enable=true"
      - "traefik.http.routers.go.rule=Path(`/`)"
      - "traefik.http.services.go.loadbalancer.server.port=80"

volumes:
  m-volume-01: null
  m-volume-02: null
  db-data: null

networks:
  m-network-01: {}
  m-network-02: {}

secrets:
  db-password:
    file: db/password.txt
```
</details>

1. Services

- Services như là cấu hình cho từng containers.

- Có nhiều cái đặt có thể được thiết lập cho từng services, khiến ta có thể khai thác chúng sâu hơn.


2. Volumes & Networks

- Volumes là vùng nhớ vật lý trên ổ đĩa, được chia sẽ chung giữa `host` và `container`, thậm trí giữa các `containers` với nhau.

- Networks cũng là nơi giao tiếp giữa các `containers` và giữa một `container` và `host`.

3. Build an Image

- Ta có thể build một `image` từ source code bằng việc đọc `Dockerfile` của nó: sử dụng keyword `build` và truyền đường dẫn tới thư mục chứa `Dockerfile`.

```dockerfile
# build: https://github.com/my-company/my-project.git
# build: ./
build:
  context: ContextPath/ # ./
  dockerfile: Dockerfile
```

4. Configuring the Networking

```dockerfile
services:
  m-service-02:
    image: alpine:latest
    container_name: container-02
    ports:
      - "8080:3000"
    expose:
      - "80"
    networks:
      - m-network-02
networks:
  m-network-02: {}
```

5. Setting Up the Volumes

- Ta có thể `mount` một `volume` ở chế độ `read-only` bằng việc thêm `:ro` vào cuối `rule` mount.

```dockerfile
services:
  m-service-02:
    image: alpine:latest
    volumes:
      - m-volume-01:/my-volumes/m-volume
      - /tmp:/my-volumes/host-volume
      - /home:/my-volumes/readonly-host-volume:ro
volumes:
  m-volume-01: null
```

6. Declaring the Dependencies

```dockerfile
services:
  m-service-01:
    image: ubuntu:latest
  m-service-02:
    image: ubuntu:latest
    depends_on:
      - m-service-01
```

7. Managing Environment Variables

```dockerfile
services:
  database: 
    image: "postgres:${POSTGRES_VERSION}"
    environment:
      - ENV-01: "${VAR}"
      - ENV-02: "${USER}"
      - MYSQL_DATABASE=example
      - MYSQL_ROOT_PASSWORD_FILE=/run/secrets/db-password
```

8. Scaling & Replicas

```dockerfile
services:
  worker:
    image: dockersamples/examplevotingapp_worker
    networks:
      - frontend
      - backend
    deploy:
      mode: replicated
      replicas: 6
      resources:
        limits:
          cpus: '0.50'
          memory: 50M
        reservations:
          cpus: '0.25'
          memory: 20M
```

## Lifecycle Management

1. Startip

- Để tạo và start `containers`, `networks` và `volumes`:

```bash
docker-compose [-f custom-compose-file.yml] up
```

- Sau lần đầu tiên, chỉ cần dùng lệnh `start`:

```bash
docker-compose [-f custom-compose-file.yml] start
```

- Chạy compose ở background

```bash
docker-compose up -d
```

2. Shutdown

- Sử dụng `stop` để dừng an toàn các services đang chạy. nó giúp bảo toàn `containers`, `volumes` và `networks`

```bash
docker-compose stop
```

- Reset toàn bộ project, nó sẽ xóa toàn bộ mọi thứ, trừ `external volumes`.

```bash
docker-compose down
```

## AWESOME DOCKER COMPOSE
<details>
  <summary>AWESOME DOCKER COMPOSE EXAMPLE!</summary>

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
 
