# Gitlab

## Install GitLab using Docker Engine

```bash
sudo mkdir -p /srv/gitlab
export GITLAB_HOME=/srv/gitlab
sudo docker run --detach \
  --hostname gitlab.example.com \
  --publish 443:443 --publish 80:80 --publish 22:22 \
  --name gitlab \
  --restart always \
  --volume $GITLAB_HOME/config:/etc/gitlab \
  --volume $GITLAB_HOME/logs:/var/log/gitlab \
  --volume $GITLAB_HOME/data:/var/opt/gitlab \
  --shm-size 256m \
  gitlab/gitlab-ee:latest
```

This will download and start a GitLab container and publish ports needed to access SSH, HTTP and HTTPS. All GitLab data will be stored as subdirectories of $GITLAB_HOME. The container will automatically restart after a system reboot.

The GitLab container uses host mounted volumes to store persistent data:

|Local location|Container location|Usage|
|:---:|---|---|
|$GITLAB_HOME/data|/var/opt/gitlab|For storing application data.|
|$GITLAB_HOME/logs|/var/log/gitlab|For storing logs.|
|$GITLAB_HOME/config|/etc/gitlab|For storing the GitLab configuration files.|

##  Install GitLab using Docker Compose

With Docker Compose you can easily configure, install, and upgrade your Docker-based GitLab installation:

1. [Install Docker Compose](https://docs.docker.com/compose/install/).
2. Create a `docker-compose.yml` file:

  <details>
    <summary>docker-compose-gitea.yml</summary>

  ```bash
  version: "3"

  networks:
    gitlab:
      external: false

  volumes:
    config-volume:
      driver: local
    log-volume:
      driver: local
    data-volume:
      driver: local

  services:
    server:
      image: 'gitlab/gitlab-ce:16.7.0-ce.0'
      container_name: gitlab
      restart: always
      hostname: 'gitlab.example.com'
      environment:
        GITLAB_OMNIBUS_CONFIG: |
          external_url 'http://gitlab.example.com:8001'
          gitlab_rails['gitlab_shell_ssh_port'] = 2223
      networks:
        - gitlab
      ports:
        - '8001:8001'
        - '2223:22'
      volumes:
        - config-volume:/etc/gitlab
        - log-volume:/var/log/gitlab
        - data-volume:/var/opt/gitlab
      shm_size: '256m'
  ```

  </details>

3. Make sure you are in the same directory as `docker-compose.yml` and start GitLab:

```bash
docker compose up -d
```





