# docker-compose.yml

```yml
version: '3.8'

services:
  portainer:
    image: portainer/portainer-ce:latest
    container_name: portainer
    ports:
      - "8004:9000"
      - "9443:9443"
    volumes:
      - /var/run/docker.sock:/var/run/docker.sock
      - portainer_data:/data
    restart: always

volumes:
  portainer_data:
    driver: local

```

## Connect to Agent

`Settings` > `Environments` > `Add environment` > `Docker Standalone` > `Start Wizard` > Run `docker run` command on agent and fill `name` and `agent address` > `Close`
