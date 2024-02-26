# [How to Create a Systemd Service in Linux](https://www.tecmint.com/create-systemd-service-linux/)

- A `systemd` service is defined in a unit file (a unit is a representation of a service and system resources such as devices, sockets, mount points, etc.)

- Custom service unit files should be stored in the `/etc/systemd/system/` directory and must have an `.service` extension.

- In Linux create a new systemd service and manage the service using the [`systemctl`](https://www.tecmint.com/manage-services-using-systemd-and-systemctl-in-linux/) command.

## Creating Custom Systemd Service File in Linux

1. Create `service` file in `/etc/systemd/system/`

   ```bash
   nano /etc/systemd/system/test-app.service
   ```

   ```service
   [Unit]
   Description=Daemon for serving test-app
   After=network.target

   [Service]
   User=1000
   Group=1000
   WorkingDirectory=/home/emoi/Downloads/Miscellaneous/zxz
   Environment=FLASK_APP=fhost FLASK_ENV=production
   ExecStart=/home/emoi/anaconda3/envs/zxz/bin/flask prune
   ExecReload=/usr/bin/kill -s HUP $MAINPID
   Restart=on-success
   RestartSec=60

   [Install]
   WantedBy=multi-user.target
   ```

  - `Description` – is used to specify a description for the service.
  - `After` – defines a relationship with a second unit, the network.target. In this case, the test-app.service is activated after the network.target unit.
  - `User` – is used to specifying the user with whose permissions the service will run.
  - `Group` – is used to specify the group with whose permissions the service will run.
  - `WorkingDirectory` – is used to set the working directory for executed processes.
  - `Environment` – is used to set environment variables for executed processes.
  - `ExecStart` – is used to define the commands with their arguments that are executed when this service is started.
  - `ExecReload` – is used to define the commands to execute to trigger a configuration reload in the service.
  - `WantedBy` – enables a symbolic link to be created in the `.wants/` or `.requires/` directory of each of the listed unit(s), `multi-user.target` in this case, when the test-app.service unit is enabled using the systemctl enable command.
  - `Restart` – directive in a systemd unit file specifies the conditions under which the service should be restarted if it exits unexpectedly.
    - `always`: The service will be automatically restarted whenever it exits, regardless of the exit status or reason.
    - `no`: The service will not be automatically restarted.
    - `on-success`: The service will be restarted only if it exits with a successful (zero) exit status.
    - `on-failure`: The service will be restarted only if it exits with a non-zero exit status.
    - `on-abnormal`: The service will be restarted only if it exits due to a signal.
    - `on-abort`: The service will be restarted only if it exits due to an abort signal.

2. Reload systemd with this new service unit file.

   ```bash
   systemctl daemon-reload
   ```

## Manage Systemd Service in Linux

1. Start/activate the service

   ```bash
   systemctl start test-app.service
   ```

2. Check if the service is running or not

   ```bash
   systemctl status test-app.service
   ```

3. Enable the service to **start at system boot**

   ```bash
   systemctl enable test-app.service
   systemctl is-enabled test-app.service
   ```

4. Disable a service to prevent it from starting at system boot

   ```bash
   systemctl disable test-app.service
   ```

5. Stop/deactivate the service

   ```bash
   systemctl stop test-app.service
   ```

6. Restart the service

   ```bash
   systemctl restart test-app.service
   ```

# [Working with `systemd` Timers](https://documentation.suse.com/smart/systems-management/html/systemd-working-with-timers/index.html)

- WHAT?
    
  - From running a backup script at regular intervals to starting a specific process as soon as the machine boots, there are plenty of tasks that require scheduling on a Linux system. `systemd timers` provide a flexible mechanism for scheduling and managing jobs and services.

## Creating a timer

- The following example shows how to set up a timer that triggers the `helloworld.sh` shell script after boot time and repeats its execution every 24 hours relative to its activation time. It also runs Monday to Friday at 10 a.m.

1. Create the file `/etc/systemd/system/helloworld.service` with the following content:

   ```
   [Unit]
   Description="Hello World script"

   [Service]
   ExecStart=/usr/local/bin/helloworld.sh
   ```

2. Create the file `/etc/systemd/system/helloworld.timer` with the following content:

   ```
   [Unit]
   Description="Run helloworld.service 5min after boot and every 24 hours relative to activation time"

   [Timer]
   OnBootSec=5min
   OnUnitActiveSec=24h
   OnCalendar=Mon..Fri *-*-* 10:00:*
   Unit=helloworld.service

   [Install]
   WantedBy=multi-user.target
   ```
