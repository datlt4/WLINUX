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

4. You’ll need to access the automatically generated root password with the command:
   
```bash
docker exec -it gitlab bash -c "cat /etc/gitlab/initial_root_password | grep 'Password: ' | awk -F' ' '{print \$2}'"
```

5. Login admin account with username `root` and the automatically generated password.

6. Check sign-up restrictions

Your GitLab instance allows anyone to register for an account, which is a security risk on public-facing GitLab instances. You should deactivate new sign ups if public users aren't expected to register for an account.

- `Search or go to...` > `Settings` > `General` > `Sign-up restrictions` > `Expand` > Disable `Sign-up enabled` > `Save changes`.

### SSH

- Remember add key as on gitlab web.

- add remote repo: `git remote add gitlab ssh://git@192.168.120.101:2223/datlt4/gst-learn.git`

### Control

- Use `gitlab_tools.sh` to start, stop gitea server and also backup and restore gitea data.

  <details>
    <summary>gitea_tools.sh</summary>

  ```bash
  # !/usr/bin/env bash
  
  # XTERM Color
  case "$TERM" in xterm-color | *-256color) color_prompt=yes ;;
  esac
  
  # define function
  print_with_color() {
      local str="$1"
      local color="$2"
      if [ "$color_prompt" = yes ]; then
          printf "${color}${str}\033[0m"
      else
          printf "${str}"
      fi
  }
  
  exit_with_error_code() {
      local error_code=$1
      local message="$2"
      if [ ${error_code} -gt 0 ]; then
          print_with_color "$message" "\033[1m\033[31m"
          exit ${error_code}
      fi
  }
  
  write_target_to_env() {
      target_value="$1"
      env_file="$2"
      if [ -z "${env_file}" ]; then
          env_file=".env"
      fi
  
      # Check if .env file exists
      if [ -f "$env_file" ]; then
          # Check if TARGET line exists in .env file
          if grep -q "^TARGET=.*" "$env_file"; then
              # Replace existing TARGET line with TARGET=latest
              sed -i "s/^TARGET=.*/TARGET=$target_value/" "$env_file"
          else
              # Insert TARGET=latest at the end of .env file
              echo "TARGET=$target_value" >> "$env_file"
          fi
      else
          # Create .env file and add TARGET=latest
          echo "TARGET=$target_value" > "$env_file"
      fi
  }
  
  # Define variable
  flag_BACKUP=0
  flag_find_BACKUP=0
  target_BACKUP="$(date +%Y%m%d_%H%M%S)"
  
  flag_RESTORE=0
  flag_find_RESTORE=0
  target_RESTORE=""
  
  flag_START_GITLAB=1
  flag_STOP_GITLAB=0
  
  flag_DELETE_RESOURCE=0
  flag_RESTART=0
  
  docker_compose_yml="docker-compose.yml"
  backup_dir="backup/"
  
  DEBUG=0
  N_BACKUP_KEEP=10
  
  # Parse input arguments
  while [[ "$#" -gt 0 ]]; do
      case $1 in
          -b | --backup | "-b " | "--backup ")
              flag_BACKUP=1
              flag_find_BACKUP=1
              flag_find_RESTORE=0
              ;;
          -r | --restore | "-r " | "--restore ")
              flag_RESTORE=1
              flag_find_BACKUP=0
              flag_find_RESTORE=1
              ;;
          -f | --file | "-f " | "--file ")
              docker_compose_yml="$2"
              flag_find_BACKUP=0
              flag_find_RESTORE=0
              shift
              ;;
          -s | --stop | "-s " | "--stop ")
              flag_find_BACKUP=0
              flag_find_RESTORE=0
              flag_STOP_GITLAB=1
              ;;
          --down | "--down ")
              flag_find_BACKUP=0
              flag_find_RESTORE=0
              flag_DELETE_RESOURCE=1;
              ;;
          --restart | "--restart ")
              flag_find_BACKUP=0
              flag_find_RESTORE=0
              flag_RESTART=1
              ;;
          -h | --help | "-h " | "--help ")
              flag_find_BACKUP=0
              flag_find_RESTORE=0
              print_with_color "[ START GITLAB ]" "\033[43m"; print_with_color " bash ./gitlab_tools.sh [-f/--file [Compose_config]]\n" "\033[93m\033[4m"
              print_with_color "  | Launch gitlab server and database\n" "\033[1m\033[33m"
              print_with_color "  | <Compose_config>" "\033[1m\033[33m"; print_with_color "(optional)" "\033[1m\033[33m\033[3m"; print_with_color " : Compose configuration files. Default \`docker-compose.yml\`.\n" "\033[33m"
              print_with_color "  | -- " "\033[1m\033[35m"; print_with_color "Example : " "\033[1m\033[35m\033[2m"; print_with_color "bash ./gitlab_tools.sh\n" "\033[1m\033[35m\033[2m\033[3m"
              print_with_color "  | -- " "\033[1m\033[35m"; print_with_color "Example : " "\033[1m\033[35m\033[2m"; print_with_color "bash ./gitlab_tools.sh -f docker-compose-gitlab.yml\n" "\033[1m\033[35m\033[2m\033[3m"
              print_with_color "[ STOP GITLAB ]" "\033[43m"; print_with_color " bash ./gitlab_tools.sh [-f/--file [Compose_config]] [-s/--stop]\n" "\033[93m\033[4m"
              print_with_color "  | Stop gitlab server and database\n" "\033[1m\033[33m"
              print_with_color "  | <Compose_config>" "\033[1m\033[33m"; print_with_color "(optional)" "\033[1m\033[33m\033[3m"; print_with_color " : Compose configuration files. Default \`docker-compose.yml\`.\n" "\033[33m"
              print_with_color "  | -- " "\033[1m\033[35m"; print_with_color "Example : " "\033[1m\033[35m\033[2m"; print_with_color "bash ./gitlab_tools.sh -s\n" "\033[1m\033[35m\033[2m\033[3m"
              print_with_color "  | -- " "\033[1m\033[35m"; print_with_color "Example : " "\033[1m\033[35m\033[2m"; print_with_color "bash ./gitlab_tools.sh -f docker-compose-gitlab.yml -s\n" "\033[1m\033[35m\033[2m\033[3m"
              print_with_color "[ RESTART GITLAB ]" "\033[43m"; print_with_color " bash ./gitlab_tools.sh [-f/--file [Compose_config]] [--restart]\n" "\033[93m\033[4m"
              print_with_color "  | Restart gitlab server and database\n" "\033[1m\033[33m"
              print_with_color "  | <Compose_config>" "\033[1m\033[33m"; print_with_color "(optional)" "\033[1m\033[33m\033[3m"; print_with_color " : Compose configuration files. Default \`docker-compose.yml\`.\n" "\033[33m"
              print_with_color "  | -- " "\033[1m\033[35m"; print_with_color "Example : " "\033[1m\033[35m\033[2m"; print_with_color "bash ./gitlab_tools.sh --restart\n" "\033[1m\033[35m\033[2m\033[3m"
              print_with_color "  | -- " "\033[1m\033[35m"; print_with_color "Example : " "\033[1m\033[35m\033[2m"; print_with_color "bash ./gitlab_tools.sh -f docker-compose-gitlab.yml --restart\n" "\033[1m\033[35m\033[2m\033[3m"
              print_with_color "[ BACKUP DB ]" "\033[43m"; print_with_color " bash ./gitlab_tools.sh [-f/--file [Compose_config]] [-b/--backup [<BACKUP_ID>]\n" "\033[93m\033[4m"
              print_with_color "  | Compress database and gitlab config to tar.gz file\n" "\033[1m\033[33m"
              print_with_color "  | <Compose_config>" "\033[1m\033[33m"; print_with_color "(optional)" "\033[1m\033[33m\033[3m"; print_with_color " : Compose configuration files. Default \`docker-compose.yml\`.\n" "\033[33m"
              print_with_color "  | <BACKUP_ID>" "\033[1m\033[33m"; print_with_color "(optional)" "\033[1m\033[33m\033[3m"; print_with_color " : Build ID specificed by user. Default is current datetime.\n" "\033[33m"
              print_with_color "  | -- " "\033[1m\033[35m"; print_with_color "Example : " "\033[1m\033[35m\033[2m"; print_with_color "bash ./gitlab_tools.sh -b\n" "\033[1m\033[35m\033[2m\033[3m"
              print_with_color "  | -- " "\033[1m\033[35m"; print_with_color "Example : " "\033[1m\033[35m\033[2m"; print_with_color "bash ./gitlab_tools.sh -b latest\n" "\033[1m\033[35m\033[2m\033[3m"
              print_with_color "  | -- " "\033[1m\033[35m"; print_with_color "Example : " "\033[1m\033[35m\033[2m"; print_with_color "bash ./gitlab_tools.sh -b \$(date)\n" "\033[1m\033[35m\033[2m\033[3m"
              print_with_color "  | -- " "\033[1m\033[35m"; print_with_color "Example : " "\033[1m\033[35m\033[2m"; print_with_color "bash ./gitlab_tools.sh -b \$(date) -f docker-compose-gitlab.yml\n" "\033[1m\033[35m\033[2m\033[3m"
              print_with_color "[ RESTORE DB ]" "\033[43m"; print_with_color " bash ./gitlab_tools.sh [-f/--file [Compose_config]] [-r/--restore [<BACKUP_ID>]\n" "\033[93m\033[4m"
              print_with_color "  | Extract tar.gz file and copy database and gitlab config to docker-volume\n" "\033[1m\033[33m"
              print_with_color "  | <Compose_config>" "\033[1m\033[33m"; print_with_color "(optional)" "\033[1m\033[33m\033[3m"; print_with_color " : Compose configuration files. Default \`docker-compose.yml\`.\n" "\033[33m"
              print_with_color "  | <BACKUP_ID>" "\033[1m\033[33m"; print_with_color "(optional)" "\033[1m\033[33m\033[3m"; print_with_color " : backup ID specificed by user. Default is latest backup file saved on backup/ directory.\n" "\033[33m"
              print_with_color "  | -- " "\033[1m\033[35m"; print_with_color "Example : " "\033[1m\033[35m\033[2m"; print_with_color "bash ./gitlab_tools.sh -r\n" "\033[1m\033[35m\033[2m\033[3m"
              print_with_color "  | -- " "\033[1m\033[35m"; print_with_color "Example : " "\033[1m\033[35m\033[2m"; print_with_color "bash ./gitlab_tools.sh -r latest\n" "\033[1m\033[35m\033[2m\033[3m"
              print_with_color "  | -- " "\033[1m\033[35m"; print_with_color "Example : " "\033[1m\033[35m\033[2m"; print_with_color "bash ./gitlab_tools.sh -r -f docker-compose-gitlab.yml\n" "\033[1m\033[35m\033[2m\033[3m"
              print_with_color "[ DELETE RESOURCES ]" "\033[43m"; print_with_color " bash ./gitlab_tools.sh [-f/--file [Compose_config]] [--down]\n" "\033[93m\033[4m"
              print_with_color "  | Stop and remove resources\n" "\033[1m\033[33m"
              print_with_color "  | <Compose_config>" "\033[1m\033[33m"; print_with_color "(optional)" "\033[1m\033[33m\033[3m"; print_with_color " : Compose configuration files. Default \`docker-compose.yml\`.\n" "\033[33m"
              print_with_color "  | -- " "\033[1m\033[35m"; print_with_color "Example : " "\033[1m\033[35m\033[2m"; print_with_color "bash ./gitlab_tools.sh --down\n" "\033[1m\033[35m\033[2m\033[3m"
              print_with_color "[ HELP ] " "\033[43m"; print_with_color "bash ./run.sh [-h/--help]\n" "\033[93m\033[4m"
              print_with_color "  | User Manual\n" "\033[1m\033[33m"
              print_with_color "  | -- " "\033[1m\033[35m"; print_with_color "Example : bash ./run.sh --help\n" "\033[1m\033[35m\033[2m\033[3m"
              exit 0
              ;;
          *)
  
          if [ ${flag_find_BACKUP} -gt 0 ]; then
              target_BACKUP=$1
              flag_find_BACKUP=0
          elif [ ${flag_find_RESTORE} -gt 0 ]; then
              target_RESTORE=$1
              flag_find_RESTORE=0
          else
              echo "Unknown parameter passed: ?$1?"
              exit 1
          fi
          ;;
      esac
      shift
  done
  
  # Check docker-compose
  eval "which docker-compose"
  exit_with_error_code "$?" "docker-compose is not installed properly"
  eval "which docker"
  exit_with_error_code "$?" "docker is not installed properly"
  
  # Check docker_compose.yml file
  if ! [ -f ${docker_compose_yml} ]; then
      exit_with_error_code 1 "Not found \`${docker_compose_yml}\`"
  fi
  
  # Check backup directory
  if [ ${flag_RESTORE} -gt 0 ]; then
      if [ -d ${backup_dir} ]; then
          if [ -z "${target_RESTORE}" ]; then
              target_RESTORE=$(ls -t1 ${backup_dir} | head -n 1 | awk -F '.' '{ print $1 }' | awk -F '_' '{ print $3 "_" $4  }')
              if [ -z "${target_RESTORE}" ]; then
                  exit_with_error_code 1 "Cannot find valid backup_id in \`${backup_dir}\` automatically"
              fi
          fi
      else
          exit_with_error_code 1 "Not found \`${backup_dir}\`"
      fi
  fi
  
  # Delete resource
  if [ ${flag_DELETE_RESOURCE} -gt 0 ]; then
      # Delete confirmation
      while true; do
          if [ "$color_prompt" = yes ]; then
              read -p "\033[1m\033[31mAre you sure you want to stop and remove all resource?\033[0m"$'\n\033[1m\033[31m      Proceed? (Yes/No) \033[0m' ans
          else
              read -p "Are you sure you want to stop and remove all resource?"$'\n      Proceed? (Yes/No) ' ans
          fi
          case $ans in
              [Yy]* ) break;;
              [Nn]* ) print_with_color "Aborted by user.\n" "\033[31m"; exit 0;;
              * ) print_with_color "  Please type \"Yes\" or \"No\".\n" "\033[31m";;
          esac
      done
  
      print_with_color "$ docker-compose -f ${docker_compose_yml} down\n" "\033[36m"
      eval "docker-compose -f ${docker_compose_yml} down"
      print_with_color "$ docker volume rm gitlab_config-volume\n" "\033[36m"
      eval "docker volume rm gitlab_config-volume"
      print_with_color "$ docker volume rm gitlab_data-volume\n" "\033[36m"
      eval "docker volume rm gitlab_data-volume"
      print_with_color "$ docker volume rm gitlab_log-volume\n" "\033[36m"
      eval "docker volume rm gitlab_log-volume"
      exit 0
  fi
  
  # Restart server
  if [ ${flag_RESTART} -gt 0 ]; then
      print_with_color "$ docker-compose -f ${docker_compose_yml} restart server\n" "\033[36m"
      eval "docker-compose -f ${docker_compose_yml} restart server"
      exit 0
  fi
  
  # Stop server
  if [ ${flag_STOP_GITLAB} -gt 0 ] || [ ${flag_BACKUP} -gt 0 ] || [ ${flag_RESTORE} -gt 0 ]; then
      print_with_color "$ docker-compose -f ${docker_compose_yml} stop\n" "\033[36m"
      eval "docker-compose -f ${docker_compose_yml} stop"
      if [ ${flag_STOP_GITLAB} -gt 0 ]; then
          exit 0
      fi
  fi
  
  # Backup/Restore server
  if [ ${flag_BACKUP} -gt 0 ]; then
      write_target_to_env ${target_BACKUP}
      print_with_color "$ docker-compose -f ${docker_compose_yml} run --rm backup\n" "\033[36m"
      eval "docker-compose -f ${docker_compose_yml} run --rm backup"
      print_with_color "$ ls -1t backup/ | tail -n+$((2 * N_BACKUP_KEEP + 1)) | xargs -I {} rm backup/{}\n" "\033[36m"
      eval "ls -1t backup/ | tail -n+$((2 * N_BACKUP_KEEP + 1)) | xargs -I {} rm backup/{}"
  elif [ ${flag_RESTORE} -gt 0 ]; then
      while true; do
          if [ "$color_prompt" = yes ]; then
              read -p "\033[1m\033[31mRestore will delete all current data. Are you sure?\033[0m"$'\n\033[1m\033[31m      Proceed? (Yes/No) \033[0m' ans
          else
              read -p "Restore will delete all current data. Are you sure?"$'\n      Proceed? (Yes/No) ' ans
          fi
          case $ans in
              [Yy]* )
                  write_target_to_env ${target_RESTORE}
                  print_with_color "$ docker-compose -f ${docker_compose_yml} run --rm restore\n" "\033[36m"
                  eval "docker-compose -f ${docker_compose_yml} run --rm restore"
                  break
                  ;;
              [Nn]* )
                  print_with_color "Aborted by user.\n" "\033[31m"
                  break
                  ;;
              * ) print_with_color "  Please type \"Yes\" or \"No\".\n" "\033[31m";;
          esac
      done
  fi
  
  # Start server
  if [ ${flag_START_GITLAB} -gt 0 ] || [ ${flag_BACKUP} -gt 0 ] || [ ${flag_RESTORE} -gt 0 ]; then
      print_with_color "$ docker-compose -f ${docker_compose_yml} up -d server\n" "\033[36m"
      eval "docker-compose -f ${docker_compose_yml} up -d server"
  fi
  ```

  </details>
