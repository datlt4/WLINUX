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

~~Go to [Silab webpage](https://www.silabs.com/developers/usb-to-uart-bridge-vcp-drivers) and select Downloads tab.~~

~~Reference: http://headstation.com/archives/instructions-installing-cp210x-serial-bridge-driver/~~

- Install dependencies

    ```bash
    sudo apt install linux-headers-$(uname -r) -y
    mkdir -p Linux_3.x.x_4.x.x_VCP_Driver_Source/
    cd Linux_3.x.x_4.x.x_VCP_Driver_Source/
    printf "obj-m = cp210x.o
    KDIR = /lib/modules/`uname -r`/build
    SRCDIR = \$(PWD)
    # try this instead if you don't have PWD defined
    # SRCDIR = \$(shell dirname \$(realpath \$(lastword \$(MAKEFILE_LIST))))
    all:
        \$(MAKE) -C \$(KDIR) M=\$(SRCDIR) modules
    clean:
        \$(MAKE) -C \$(KDIR) M=\$(SRCDIR) clean
    " > Makefile
    ```

- Download [`cp210x.c`](https://elixir.bootlin.com/linux/v6.8/source/drivers/usb/serial/cp210x.c) corresponding to the kernel version and place in `Linux_3.x.x_4.x.x_VCP_Driver_Source/`.

- Then run `make all` to build module

    ```bash
    make all
    sudo cp cp210x.ko /lib/modules/$(uname -r)/kernel/drivers/usb/serial
    sudo insmod /lib/modules/$(uname -r)/kernel/drivers/usb/serial/usbserial.ko
    sudo insmod cp210x.ko
    # run `sudo rmmod cp210x.ko` if existed
    ```


## ESP-IDF with Visual Studio Code

- Step 1: Install `C/C++` extention
- Step 2: `mkdir .vscode`
- Step 3: Create new file named as `c_cpp_properties.json` with content:
```
{
    "configurations": [
        {
            "name": "Linux",
            "includePath": [
                "~/esp/esp-idf/components/**",
                "${workspaceFolder}/**"
            ],
            "browse": {
                "path": [
                    "/home/m/esp/esp-idf/components/**",
                    "${workspaceFolder}/**"
                ],
                "limitSymbolsToIncludedHeaders": false
            },
            "compilerPath": "~/.espressif/tools/xtensa-esp32-elf/esp-2020r3-8.4.0/xtensa-esp32-elf/bin/xtensa-esp32-elf-gcc",
            "cStandard": "c11",
            "cppStandard": "c++17"
        }
    ],
    "version": 4
}
```
