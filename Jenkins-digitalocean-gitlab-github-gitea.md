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

- To start this setup based on `docker-compose`, execute `docker-compose -f docker-compose-gitea.yml up -d `, to launch Gitea in the background. Using `docker-compose ps` will show if Gitea started properly. Logs can be viewed with `docker-compose logs`.

- To shut down the setup, execute `docker-compose down`. This will stop and kill the containers. The volumes will still exist.

- Notice: if using a non-3000 port on http, change `app.ini` to match `LOCAL_ROOT_URL = http://localhost:3000/`.

### `docker-compse-gitea.yml`

```yml
version: "3"

networks:
  gitea:
    external: false

volumes:
  gitea:
    driver: local
  mysql-gitea:
    driver: local
  postgres-gitea:
  	driver: local

services:
  server:
    image: gitea/gitea:1.21.0
    container_name: gitea
    # environment:
    # 	- USER_UID=1000
    #   - USER_GID=1000
    #   - GITEA__database__DB_TYPE=mysql
    #   - GITEA__database__HOST=db:3306
    #   - GITEA__database__NAME=gitea
    #   - GITEA__database__USER=gitea
    #   - GITEA__database__PASSWD=gitea
    restart: always
    networks:
      - gitea
    volumes:
      - ./gitea:/data
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
      - mysql-gitea:/var/lib/mysql

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
  #     - postgres-gitea:/var/lib/postgresql/data
```

























