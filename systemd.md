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
    
  - From running a backup script at regular intervals to starting a specific process as soon as the machine boots, there are plenty of tasks that require scheduling on a Linux system.
  - `systemd timers` provide a flexible mechanism for scheduling and managing jobs and services.

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

   - `Description`: A brief description explaining the timer file's purpose.
   - `OnBootSec`: Specifies a timer that triggers the service five minutes after the system boot.
   - `OnUnitActiveSec`: Specifies a timer that triggers the service 24 hours after the service has been activated.
   - `OnCalendar`: Specifies a timer that triggers the service at fixed points in time (in this example, Monday to Friday at 10 a.m.).
   - `Unit`: The service file to execute.
   - `WantedBy`: The systemd target in which the timer gets activated.

3. Start the timer

   ```bash
   sudo systemctl start helloworld.timer
   ```

4. Enable the timer to make sure that it is activated on boot

   ```bash
   sudo systemctl enable helloworld.timer
   ```

## Managing timers

1. Starting and stopping timers

   ```bash
   sudo systemctl start <TIMER>.timer
   sudo systemctl restart <TIMER>.timer
   sudo systemctl stop <TIMER>.timer
   ```

2. Enabling and disabling timers

   ```bash
   sudo systemctl enable <TIMER>.timer
   sudo systemctl disable <TIMER>.timer
   ```

3. Showing the timer file contents

   ```bash
   sudo systemctl cat <TIMER>.timer
   ```

4. Checking on a specific timer

   ```bash
   sudo systemctl status <TIMER>.timer
   ```

## Timer types

- `systemd` supports many types of timers: `real-time` (based on calendar), `monotonic` (based on events) and `transient timers` that are only valid for the current session.

1. Real-time timers

   - Real-time timers are triggered by calendar events. They are defined using the option `OnCalendar`.
   - `OnCalendar=<DayOfWeek> <Year-Month-Day> <Hour:Minute:Second>`
   - `<DayOfWeek>`. Possible values are `Mon`, `Tue`, `Wed`, `Thu`, `Fri`, `Sat`, `Sun`. Leave out to ignore the day of the week. Use two dots to define a continuous range `(Mon..Fri)`.
   - `<Year-Month-Day>`. Specify month and day by two digits, year by four digits. Each value can be replaced by the wildcard `*` to match every occurrence. Use two dots to define a continuous range `(0..30)`.
   - `<Hour:Minute:Second>`. Specify each value by two digits. Each value can be replaced by the wildcard `*` to match every occurrence. Use two dots to define a continuous range `(0..30)`.

   ```bash
   - 6 p.m. every Friday:
      OnCalendar=Fri *-*-* 18:00:00

   - 5 a.m. every day:
      OnCalendar=Mon..Sun *-*-* 5:00:00

   - 1 a.m. and 3 a.m. on Sundays and Tuesdays:
      OnCalendar=Tue,Sun *-*-* 01,03:00:00

   - Single date:
      OnCalendar=Mo..Sun 2023-09-23 00:00:01

   - To specify triggers at different times, you can create more than one OnCalendar entry in a single timer file:
      OnCalendar=Mon..Fri *-*-* 10:00
      OnCalendar=Sat,Sun *-*-* 22:00

   - To specify triggers at every Sunday and every 8h
      OnCalendar=Sun *-*-* 0/08:00:00
   ```

2. Monotonic timers

   - `Monotonic` timers are triggered at a specified time elapsed from a certain event.
   - Values are defined as time units (`minutes`, `hours`, `days`, `months`, `years`, etc.).
   - The following units are supported: `usec`, `msec`, `seconds`, `minutes`, `hours`, `days`, `weeks`, `months`, `years`. There are several options for defining monotonic timers:

   ```bash
   - OnActiveSec: time after unit activation
      OnActiveSec=50minutes

   - OnBootSec: time after system boot
      OnBootSec=10hours

   - OnStartupSec: time after the service manager is started. For system services, this is almost equal to OnActiveSec. Use this for user services where the service manager is started at user login.
      OnStartupSec=5minutes 20seconds
   
   - OnUnitActiveSec: time after the corresponding service was last activated
      OnUnitActiveSec=10seconds
   
   - OnUnitInactiveSec: time after the corresponding service was last deactivated
      OnUnitInactiveSec=2hours 15minutes 18 seconds
   ```

3. Transient timers

   - Transient timers are temporary timers that are only valid for the current session.
   - Using these timers, you can either use an existing service file or start a program directly.
   - Transient timers are invoked by running `systemd-run`.

   ```bash
   - The following example runs the helloworld.service unit every two hours:
      sudo systemd-run --on-active="2hours" --unit="helloworld.service"

   - To run a command directly, use the following syntax. In this example, the script /usr/local/bin/helloworld.sh is called directly:
      sudo systemd-run --on-active="2hours" /usr/local/bin/helloworld.sh

   - If the command takes parameters, add them separated by space:
      sudo systemd-run --on-active="2hours" /usr/local/bin/helloworld.sh --language=pt_BR
   ```

   - Transient timers can be `monotonic` or `real-time`. The following switches are supported and work as described in Monotonic timers:

   ```bash
   --on-active
   --on-startup
   --on-unit-active
   --on-unit-inactive
   --on-calendar
   ```

## Testing calendar entries

- `systemd` provides a tool for testing and creating calendar timer entries for real-time timers: `systemd-analyze calendar`.
- It accepts the same argument as the `OnCalendar` entry required to set up real-time timers.

   ```
   systemd-analyze calendar "Tue,Sun *-*-* 01,03:00:00"
   systemd-analyze calendar "Mon..Fri *-*-* 10:00" "Sat,Sun *-*-* 22:00"
   systemd-analyze calendar --iterations 5 "Sun *-*-* 0/08:00:00"
   ```

## Using timers as a regular user

- `systemd` timers can also be used by regular users.
- It helps you to automate recurring tasks like backups, processing images, or moving data to the cloud.
- The same procedures and tasks as for system-wide timers are valid. However, the following differences apply:

   - Timer and service files must be placed in `~/.config/systemd/user/`.

   ```bash
   systemctl --user start ~/.config/systemd/user/helloworld.timer
   systemctl --user enable ~/.config/systemd/user/helloworld.timer
   systemctl --user list-timers
   journalctl --user -u helloworld.*
   systemd-analyze verify ~/.config/systemd/user/helloworld.timer
   ```
