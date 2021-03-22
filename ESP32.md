# Get ESP-IDF

## Standard Setup of Toolchain for Linux

### Step 1. Install Prerequisites

```
sudo apt-get install git wget flex bison gperf python3 python3-pip python3-setuptools cmake ninja-build ccache libffi-dev libssl-dev dfu-util libusb-1.0-0
sudo apt remove python3-pip python3-virtualenv -y
rm -r ~/.espressif/python_env && python get-pip.py
```

### Step 2. Get ESP-IDF

```
mkdir -p ~/esp
cd ~/esp
git clone --recursive https://github.com/espressif/esp-idf.git
```

### Step 3. Set up the tools
```
cd ~/esp/esp-idf
./install.sh
```

### Step 4. Set up the environment variables
```
. $HOME/esp/esp-idf/export.sh
```

### Step 5. Start a Project
```
cd ~/esp
cp -r $IDF_PATH/examples/get-started/hello_world .
```

### Step 6. Connect Your Device
```
Linux: starting with /dev/tty
```

### Step 7. Configure
```
cd ~/esp/hello_world
idf.py set-target esp32
idf.py menuconfig
```

### Step 8. Build the Project
```
idf.py build
```

### Step 9. Flash onto the Device
```
idf.py -p PORT [-b BAUD] flash
```
example
```
idf.py -p /dev/ttyUSB0 -b 460800 flash
```

### Step 10. Monitor
```
idf.py -p /dev/ttyUSB0 monitor
```

## Install CP210x USB to UART Bridge VCP Drivers

Go to [Silab webpage](https://www.silabs.com/developers/usb-to-uart-bridge-vcp-drivers) and select Downloads tab.

Reference: http://headstation.com/archives/instructions-installing-cp210x-serial-bridge-driver/

