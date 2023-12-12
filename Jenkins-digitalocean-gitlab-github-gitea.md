# Digital Ocean

## Create new Droplet

```bash
Create > Droplets > Marketplace > chọn Docker ... > chọn plan > chọn region > Add SSH > Choose a hostname
```

## Connect

- SSH

```bash
ssh -i <openssh-key> root@<ip address> -p 22 
```

## Modify Docker daemon to open Docker port to LAN

- Get IP with `ifconfig`

```bash
ifconfig
```

- Modify `/lib/systemd/system/docker.service` with change

```bash
ExecStart=/usr/bin/dockerd -H unix://var/run/docker.sock -H tcp://<digital ocean ip address> --containerd=/run/containerd/containerd.sock

example:
ExecStart=/usr/bin/dockerd -H unix://var/run/docker.sock -H tcp://10.137.0.2 --containerd=/run/containerd/containerd.sock
```

- Restart service docker

```bash
systemctl daemon-reload
systemctl restart docker
systemctl status docker
```

- Create user `jenkins`

```bash
export USR=jenkins
ssh-keygen -q -N '' -m PEM -t rsa -f "$HOME/.ssh/id_rsa_$USR" <<< ""$'\n'"y" 2>&1 >/dev/null

# create new user
useradd -m -d /home/$USR -s /bin/bash $USR
usermod -aG docker $USR
mkdir -p /home/$USR/.ssh
touch /home/$USR/.ssh/authorized_keys
cat "$HOME/.ssh/id_rsa_$USR.pub" >> /home/$USR/.ssh/authorized_keys
ssh -i $HOME/.ssh/id_rsa_$USR $USR@localhost "docker --version && echo '>>> DONE. New user added'"
```

- Activate new user

```bash
su jenkins
```

- Run Jenkins and mount Docker services in host to jenkins container

```bash
id
docker volume create jenkins_volume
docker run -v /var/run/docker.sock:/var/run/docker.sock -v $(which docker):$(which docker) -v jenkins_volume:/var/jenkins_home -p 8081:8080 --user 1000:999 --name jenkins -d jenkins/jenkins:lts
```

trong đó `1000`: là user-id, `999`: docker group-id

- Modify Jenkins port `/lib/systemd/system/jenkins.service` with change:

```bash
Environment="JENKINS_PORT=xxxx"
```

# Jenkins

## Plugins

- Authentication Tokens API
- Build Pipeline
- Command Agent Launcher
- Docker
- Docker Commons
- Docker Pipeline
- EnvInject API
- Environment Injector
- Jersey 2 API
- Generic Webhook Trigger
- GitHub Integration
- GitLab
- Multibranch Scan Webhook Trigger
- SSH

## Jenkinsfile

<details>
  <summary>Click to expand</summary>

```bash
pipeline {
    agent none

    environment {
        DOCKER_IMAGE = 'nhtua/flask-docker'
    }

    stages {
        stage('Test') {
            agent {
                    docker {
                        image 'python:3.8-slim-buster'
                        args '-u 0:0 -v /tmp:/root/.cache'
                    }
            }
            steps {
                sh 'pip install poetry'
                sh 'poetry install'
                sh 'poetry run pytest'
            }
        }

        stage('build') {
            agent { node { label 'master' } }
            environment {
                DOCKER_TAG = "${GIT_BRANCH.tokenize('/').pop()}-${BUILD_NUMBER}-${GIT_COMMIT.substring(0, 7)}"
            }
            steps {
                withCredentials([usernamePassword(credentialsId: 'docker-hub', usernameVariable: 'DOCKER_USERNAME', passwordVariable: 'DOCKER_PASSWORD')]) {
                    sh 'echo $DOCKER_PASSWORD | docker login --username $DOCKER_USERNAME --password-stdin'
                }

                sh "docker build -t ${DOCKER_IMAGE}:${DOCKER_TAG} . "
                sh "docker push ${DOCKER_IMAGE}:${DOCKER_TAG}"
                script {
                    if (GIT_BRANCH ==~ /.*master.*/) {
                        sh "docker tag ${DOCKER_IMAGE}:${DOCKER_TAG} ${DOCKER_IMAGE}:latest"
                        sh "docker push ${DOCKER_IMAGE}:latest"
                    }
                }

                //clean to save disk
                sh "docker image rm ${DOCKER_IMAGE}:${DOCKER_TAG}"
            }
        }
    }

    post {
        success {
            echo 'SUCCESSFUL'
        }
        failure {
            echo 'FAILED'
        }
    }
}
```

</details>

<details>
  <summary>Click to expand</summary>

```bash
pipeline {
    agent any

    triggers {
        cron('0 */1 * * *')
        gitlab(triggerOnPush: true, triggerOnMergeRequest: true, branchFilterType: 'All')
    }

    stages {
        stage('TimerTrigger') {
            when {
                triggeredBy "TimerTrigger"
            }
            steps {
                echo '------------------------------------------- TimerTrigger'
                script {
                    if (env.BRANCH_NAME == 'main') {
                        sh 'echo "GIT_BRANCH: $GIT_BRANCH"'
                        sh 'echo ${SAVE_VCAST_REPORT_DIR}'
                        sh "sudo /usr/bin/bash ./run.sh -b \${GIT_BRANCH}"
                    }
                }
            }
        }
        stage('GitLabWebHookCause') {
            when {
                not {
                    triggeredBy "TimerTrigger"
                }
            }
            steps {
                echo '------------------------------------------- GitLabWebHookCause'
                script {
                    if (env.BRANCH_NAME == 'main') {
                        sh 'echo "GIT_BRANCH: $GIT_BRANCH"'
                        sh "sudo /usr/bin/bash ./run.sh -b \${GIT_BRANCH}"
                    }
                    else {
                        sh 'echo "GIT_BRANCH: $GIT_BRANCH"'
                        sh 'echo ${SAVE_VCAST_REPORT_DIR}'
                        sh "sudo /usr/bin/bash ./run.sh -b \${GIT_BRANCH}"
                    }
                }
            }
        }
    }
}

```

</details>

- Explain `args '-u 0:0 -v /tmp:/root/.cache'`:

	- `0:0`: Use root user within the Docker container.
	- `/tmp:/root/.cache`: achive python cache installation.

## Create new new Jenkins multibranch pipeline

# Github

```bash
Profile > Settings > Develops settings > Personal access tokens > Tokens (classic) > Generate new token
```

Scope define

- repo > repo:status
- admin:repo_hook > write:repo_hook
- admin:repo_hook > read:repo_hook
- user > read:user
- user > user:email
- write:discussion > read:discussion



# Gitlab


```bash
docker run --detach --hostname luongtandat.com --publish 1443:443 --publish 8082:80 --publish 2222:22 --name gitlab --restart always --volume `pwd`/gitlab_data/config:/etc/gitlab --volume `pwd`/gitlab_data/logs:/var/log/gitlab --volume `pwd`/gitlab_data/data:/var/opt/gitlab gitlab/gitlab-ce:latest
```

```bash
docker exec -it gitlab bash -c "cat /etc/gitlab/initial_root_password"
```


# Gitea

## Installation

### Basics

- The most simple setup just creates a volume and a network and starts the `gitea/gitea:latest` image as a service. Since there is no database available, one can be initialized using `SQLite3`. 
- Create a directory like gitea and paste the following content into a file named `docker-compose-gitea.yml`.

<details>
  <summary>docker-compose-gitea.yml</summary>

```yml
version: "3"

networks:
  gitea:
    external: false

services:
  server:
    image: gitea/gitea:1.21.0
    container_name: gitea
    environment:
      - USER_UID=1000
      - USER_GID=1000
    restart: always
    networks:
      - gitea
    volumes:
      - ./gitea:/data
      - /etc/timezone:/etc/timezone:ro
      - /etc/localtime:/etc/localtime:ro
    ports:
      - "3000:3000"
      - "222:22"
```
</details>

### Ports

- To bind the integrated OpenSSH daemon and the webserver on a different port, adjust the port section. It's common to just change the host port and keep the ports within the container like they are.

<details>
  <summary>docker-compose-gitea.yml</summary>

```diff
version: "3"

networks:
  gitea:
    external: false

services:
  server:
    image: gitea/gitea:1.21.0
    container_name: gitea
    environment:
      - USER_UID=1000
      - USER_GID=1000
    restart: always
    networks:
      - gitea
    volumes:
      - ./gitea:/data
      - /etc/timezone:/etc/timezone:ro
      - /etc/localtime:/etc/localtime:ro
    ports:
-     - "3000:3000"
-     - "222:22"
+     - "8080:3000"
+     - "2221:22"
```
</details>

### Databases

#### MySQL database

- To start Gitea in combination with a `MySQL` database, apply these changes to the `docker-compose-gitea.yml` file created above.

<details>
  <summary>docker-compose-gitea.yml</summary>

```diff
version: "3"

networks:
  gitea:
    external: false

services:
  server:
    image: gitea/gitea:1.21.0
    container_name: gitea
    environment:
      - USER_UID=1000
      - USER_GID=1000
+      - GITEA__database__DB_TYPE=mysql
+      - GITEA__database__HOST=db:3306
+      - GITEA__database__NAME=gitea
+      - GITEA__database__USER=gitea
+      - GITEA__database__PASSWD=gitea
    restart: always
    networks:
      - gitea
    volumes:
      - ./gitea:/data
      - /etc/timezone:/etc/timezone:ro
      - /etc/localtime:/etc/localtime:ro
    ports:
      - "3000:3000"
      - "222:22"
+    depends_on:
+      - db
+
+  db:
+    image: mysql:8
+    restart: always
+    environment:
+      - MYSQL_ROOT_PASSWORD=gitea
+      - MYSQL_USER=gitea
+      - MYSQL_PASSWORD=gitea
+      - MYSQL_DATABASE=gitea
+    networks:
+      - gitea
+    volumes:
+      - ./mysql:/var/lib/mysql
```
</details>

#### PostgreSQL database

- To start Gitea in combination with a PostgreSQL database, apply these changes to the `docker-compose-gitea.yml` file created above.

<details>
  <summary>docker-compose-gitea.yml</summary>

```diff
version: "3"

networks:
  gitea:
    external: false

services:
  server:
    image: gitea/gitea:1.21.0
    container_name: gitea
    environment:
      - USER_UID=1000
      - USER_GID=1000
+      - GITEA__database__DB_TYPE=postgres
+      - GITEA__database__HOST=db:5432
+      - GITEA__database__NAME=gitea
+      - GITEA__database__USER=gitea
+      - GITEA__database__PASSWD=gitea
    restart: always
    networks:
      - gitea
    volumes:
      - ./gitea:/data
      - /etc/timezone:/etc/timezone:ro
      - /etc/localtime:/etc/localtime:ro
    ports:
      - "3000:3000"
      - "222:22"
+    depends_on:
+      - db
+
+  db:
+    image: postgres:14
+    restart: always
+    environment:
+      - POSTGRES_USER=gitea
+      - POSTGRES_PASSWORD=gitea
+      - POSTGRES_DB=gitea
+    networks:
+      - gitea
+    volumes:
+      - ./postgres:/var/lib/postgresql/data
```
</details>

### Named volumes

- To use named volumes instead of host volumes, define and use the named volume within the `docker-compose-gitea.yml` configuration. This change will automatically create the required volume. You don't need to worry about permissions with named volumes; Docker will deal with that automatically.

<details>
  <summary>docker-compose-gitea.yml</summary>

```diff
version: "3"

networks:
  gitea:
    external: false

+volumes:
+  gitea:
+    driver: local
+
services:
  server:
    image: gitea/gitea:1.21.0
    container_name: gitea
-    environment:
-      - USER_UID=1000
-      - USER_GID=1000
    restart: always
    networks:
      - gitea
    volumes:
-      - ./gitea:/data
+      - gitea:/data
      - /etc/timezone:/etc/timezone:ro
      - /etc/localtime:/etc/localtime:ro
    ports:
      - "3000:3000"
      - "222:22"
```
</details>

### Startup

- To start this setup based on `docker-compose`

    - Execute `docker-compose -f docker-compose-gitea.yml up -d `, to launch Gitea in the background.
    - Using `docker-compose ps` will show if Gitea started properly.
    - Logs can be viewed with `docker-compose logs`.

- To shut down the setup, execute `docker-compose down`. This will stop and kill the containers. The volumes will still exist.

- `docker-compose down` removes all container.

- `docker-compose down -v` removes all volumes attached.

- Notice: if using a non-3000 port on http, change `app.ini` to match `LOCAL_ROOT_URL = http://localhost:3000/`.

### `docker-compse-gitea.yml`

- On the host, create the `git` user which shares the same UID/ GID as the container values USER_UID/ USER_GID: `sudo useradd git [-g 1000]`

- Get `git` UID and GID: `id git`, and the output like this: `uid=1001(git) gid=1000(emoi) groups=1000(emoi)`

<details>
  <summary>docker-compose-gitea.yml</summary>

```yml
version: "3"

networks:
  gitea:
    external: false

volumes:
  data-volume:
    driver: local
  mysql-volume:
    driver: local
  postgres-volume:
    driver: local

services:
  server:
    image: gitea/gitea:1.21.2
    container_name: gitea
    environment:
      - USER_UID=1001
      - USER_GID=1000
      - GITEA__database__DB_TYPE=mysql
      - GITEA__database__HOST=db:3306
      - GITEA__database__NAME=gitea
      - GITEA__database__USER=gitea
      - GITEA__database__PASSWD=gitea
      # - GITEA__database__DB_TYPE=postgres
      # - GITEA__database__HOST=db:5432
      # - GITEA__database__NAME=gitea
      # - GITEA__database__USER=gitea
      # - GITEA__database__PASSWD=gitea
    restart: always
    networks:
      - gitea
    volumes:
      - data-volume:/data
      - /etc/timezone:/etc/timezone:ro
      - /etc/localtime:/etc/localtime:ro
    ports:
      - "8000:3000"
      - "2222:22"
    depends_on:
      - db

  db:
    image: mysql:8
    restart: always
    environment:
      - MYSQL_ROOT_PASSWORD=gitea
      - MYSQL_USER=gitea
      - MYSQL_PASSWORD=gitea
      - MYSQL_DATABASE=gitea
    networks:
      - gitea
    volumes:
      - mysql-volume:/var/lib/mysql

  # db:
  #   image: postgres:14
  #   restart: always
  #   environment:
  #     - POSTGRES_USER=gitea
  #     - POSTGRES_PASSWORD=gitea
  #     - POSTGRES_DB=gitea
  #   networks:
  #     - gitea
  #   volumes:
  #     - postgres-volume:/var/lib/postgresql/data
```
</details>

### Configure

- Access `127.0.0.1:8000` for initial configuration and email configuration.

<img src="asset/gitea-initial-configuration.png" width="800"/>

<img src="asset/gitea-email-configuration.png" width="800"/>

- Then create first user, it will consider as administrator.

<img src="asset/gitea-first-account.png" width="800"/>

- And all accounts registered after will need to activate via link will sent to user's email

<img src="asset/gitea-activate-account.png" width="800"/>

- You can modify the configuration after initially by `app.ini` file

```bash
docker exec -it gitea bash
vi /data/gitea/conf/app.ini
```

<details>
  <summary>app.ini</summary>

```
APP_NAME = Gitea: Git with a cup of tea
RUN_MODE = prod
RUN_USER = git
WORK_PATH = /data/gitea

[repository]
ROOT = /data/git/repositories

[repository.local]
LOCAL_COPY_PATH = /data/gitea/tmp/local-repo

[repository.upload]
TEMP_PATH = /data/gitea/uploads

[server]
APP_DATA_PATH = /data/gitea
DOMAIN = 127.0.0.1
SSH_DOMAIN = 127.0.0.1
HTTP_PORT = 3000
ROOT_URL = http://127.0.0.1:8000/
DISABLE_SSH = false
SSH_PORT = 22
SSH_LISTEN_PORT = 22
LFS_START_SERVER = true
LFS_JWT_SECRET = *******************************************
OFFLINE_MODE = false

[database]
PATH = /data/gitea/gitea.db
DB_TYPE = mysql
HOST = db:3306
NAME = gitea
USER = gitea
PASSWD = gitea
LOG_SQL = false
SCHEMA =
SSL_MODE = disable

[indexer]
ISSUE_INDEXER_PATH = /data/gitea/indexers/issues.bleve

[session]
PROVIDER_CONFIG = /data/gitea/sessions
PROVIDER = file

[picture]
AVATAR_UPLOAD_PATH = /data/gitea/avatars
REPOSITORY_AVATAR_UPLOAD_PATH = /data/gitea/repo-avatars

[attachment]
PATH = /data/gitea/attachments

[log]
MODE = console
LEVEL = info
ROOT_PATH = /data/gitea/log

[security]
INSTALL_LOCK = true
SECRET_KEY =
REVERSE_PROXY_LIMIT = 1
REVERSE_PROXY_TRUSTED_PROXIES = *
INTERNAL_TOKEN = *********************************************************************************************************
PASSWORD_HASH_ALGO = pbkdf2

[service]
DISABLE_REGISTRATION = false
REQUIRE_SIGNIN_VIEW = false
REGISTER_EMAIL_CONFIRM = false
ENABLE_NOTIFY_MAIL = true
ALLOW_ONLY_EXTERNAL_REGISTRATION = false
ENABLE_CAPTCHA = false
DEFAULT_KEEP_EMAIL_PRIVATE = false
DEFAULT_ALLOW_CREATE_ORGANIZATION = true
DEFAULT_ENABLE_TIMETRACKING = true
NO_REPLY_ADDRESS = noreply.localhost

[lfs]
PATH = /data/git/lfs

[mailer]
ENABLED = true
SMTP_ADDR = smtp.gmail.com
SMTP_PORT = 587
FROM = ***********************************
USER = ***********************************
PASSWD = ****************

[openid]
ENABLE_OPENID_SIGNIN = true
ENABLE_OPENID_SIGNUP = true

[cron.update_checker]
ENABLED = false

[repository.pull-request]
DEFAULT_MERGE_STYLE = merge

[repository.signing]
DEFAULT_TRUST_MODEL = committer

[oauth2]
JWT_SECRET = *******************************************
```

</details>

### SSH

- Remember add key as on github

- add remote repo: `git remote add gitea ssh://git@192.168.120.103:2222/datlt4/gst-learn.git`





