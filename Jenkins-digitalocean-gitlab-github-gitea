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
# touch /home/$USR/.ssh/authorized_keys
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
docker volume create devops_volume
docker run -v /var/run/docker.sock:/var/run/docker.sock -v $(which docker):$(which docker) -v devops_volume/jenkins_data:/var/jenkins_home -p 8080:8080 --user 1000:999 --name jenkins-server -d jenkins/jenkins/lts
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

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

# Gitlab

# Gitea
