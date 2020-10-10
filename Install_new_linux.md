[REFERENCE](https://towardsdatascience.com/a-definitive-guide-for-setting-up-a-deep-learning-workstation-with-ubuntu-18-04-5459d70e19c3)

## Install `htop`

    sudo apt --assume-yes install cmake htop tree
    sudo apt-get update
    sudo apt-get --assume-yes upgrade
    sudo apt-get --assume-yes install tmux build-essential gcc g++ make binutils
    sudo apt-get --assume-yes install software-properties-common
    sudo apt-get --assume-yes install git

## Install `openssh`
    
    sudo apt install openssh-server openssh-client

## Install the latest version of `cmake`

    sudo apt remove --purge --auto-remove cmake

Download `.sh` file from [this link](https://cmake.org/download/)

    $ wget https://github.com/Kitware/CMake/releases/download/v3.18.3/cmake-3.18.3-Linux-x86_64.sh
    $ sudo sh cmake-3.18.3-Linux-x86_64.sh --prefix=/opt/cmake
    
Add to the end of file `.bashrc`

    $ export PATH=/opt/cmake/cmake-3.18.3-Linux-x86_64/bin:${PATH:+:${PATH}}

    $ cmake --version

## Install TeamVier

    sudo apt update -y && sudo apt upgrade -y
    wget https://download.teamviewer.com/download/linux/teamviewer_amd64.deb
    sudo apt install ./teamviewer_amd64.deb

## Install `Skype`

    wget https://go.skype.com/skypeforlinux-64.deb
    sudo apt install ./skypeforlinux-64.deb

Start Teamviewer

    /usr/bin/teamviewer

Get ID

    sudo teamviewer --info print version, status, id

## Install `Visual Code`

    https://code.visualstudio.com/download

## Install `Sublime Text`

    sudo apt update
    sudo apt install apt-transport-https ca-certificates curl software-properties-common -y
    curl -fsSL https://download.sublimetext.com/sublimehq-pub.gpg | sudo apt-key add -
    sudo add-apt-repository "deb https://download.sublimetext.com/ apt/stable/"
    sudo apt update
    sudo apt install sublime-text -y

## Install `ibus-unikey`

    sudo apt install ibus-unikey -y
    sudo add-apt-repository -r ppa:ubuntu-vn/ppa
    sudo apt update -q
    ibus restart

[**ERROR**] Can't connect ibus

    ibus-daemon &

## Install KDE-Plasma

    sudo apt install tasksel
    sudo tasksel install kubuntu-desktop
        - select <OK>
        - select sddm
    sudo apt install sddm
    sudo dpkg-reconfigure sddm

Customize:

    sudo apt install g++ cmake libx11-dev libxext-dev qtbase5-dev libqt5svg5-dev libqt5x11extras5-dev libqt4-dev qttools5-dev-tools libkf5windowsystem-dev git
    sudo add-apt-repository ppa:papirus/papirus
    sudo apt-get update
    sudo apt-get install --install-recommends adapta-kde 

Install Kvantum

    sudo add-apt-repository ppa:papirus/papirus
    sudo apt install qt5-style-kvantum

[**Customize KDE-Plasma - Dark Material Blur**](https://www.youtube.com/watch?v=VL7B6oBaTfs&list=PL9hShGTZRBvLMMPn6QjRJk6zklF-ZqRMo)

## Install GPU Driver - Support higher graphic resolutions or how GPU talk to python interface.

[**Download**](https://www.nvidia.com/Download/index.aspx)

    chmod +x NVIDIA-Linux-x86_64–440.44.run
    sudo sh NVIDIA-Linux-x86_64–440.44.run

[**ERROR**] `disable Nouveau nvidia driver on Ubuntu 18.04 Bionic Beaver Linux`

    sudo bash -c "echo blacklist nouveau > /etc/modprobe.d/blacklist-nvidia-nouveau.conf"
    sudo bash -c "echo options nouveau modeset=0 >> /etc/modprobe.d/blacklist-nvidia-nouveau.conf"
    cat /etc/modprobe.d/blacklist-nvidia-nouveau.conf
    sudo update-initramfs -u
    sudo reboot

[**ERROR**] `ERROR: An NVIDIA kernel module 'nvidia-drm' appears to already be loaded in your kernel.  This may be because it is in use (for example, by an X server, a CUDA program, or the NVIDIA Persistence Daemon)`

    sudo systemctl set-default multi-user.target
    sudo reboot 0

    sudo ./NVIDIA-Linux-x86_64-440.44.run

    sudo systemctl set-default graphical.target
    sudo reboot 0

[**ERROR**] `Possible missing firmware /lib/firmware/rtl_nic/rtl8105e-1.fw for module r8169 with 2.6.39 kernel`

    git clone git://git.kernel.org/pub/scm/linux/kernel/git/firmware/linux-firmware.git
    sudo cp -r linux-firmware/rtl_nic/ /lib/firmware/
    sudo update-initramfs -u



## Install CUDA - allows us a way to write code for GPUs (Install cuda 10.0 - 10.1)

    sudo apt-key adv --fetch-keys http://developer.download.nvidia.com/compute/cuda/repos/ubuntu1804/x86_64/7fa2af80.pub && echo "deb https://developer.download.nvidia.com/compute/cuda/repos/ubuntu1804/x86_64 /" | sudo tee /etc/apt/sources.list.d/cuda.list
    sudo apt-get update && sudo apt-get -o Dpkg::Options::="--force-overwrite" install cuda-10-0 cuda-drivers
    echo 'export PATH=/usr/local/cuda-10.0/bin${PATH:+:${PATH}}' >> ~/.bashrc && echo 'export LD_LIBRARY_PATH=/usr/local/cuda-10.0/lib64${LD_LIBRARY_PATH:+:${LD_LIBRARY_PATH}}' >> ~/.bashrc && source ~/.bashrc && sudo ldconfig
    nvcc --version
    nvidia-smi -l 1

## Install CuDNN - Primitives for Deep Learning Network

**[Access]**

    https://developer.nvidia.com/rdp/cudnn-download

**Download** cuDNN Runtime Library for Ubuntu18.04  (Deb)

    sudo dpkg -i libcudnn7_7.6.5.32-1+cuda10.1_amd64.deb

**Download** cuDNN Developer Library for Ubuntu18.04  (Deb)

    sudo dpkg -i libcudnn7-dev_7.6.5.32-1+cuda10.1_amd64.deb

**Download** cuDNN Code Samples and User Guide for Ubuntu18.04  (Deb)

    sudo dpkg -i libcudnn7-doc_7.6.5.32-1+cuda10.1_amd64.deb

## Install TensorRT

[ACCESS](https://developer.nvidia.com/nvidia-tensorrt-download) to download the version of TensorRT that you are interested in.

    $ os="ubuntu1804"
    $ tag="cuda10.0-trt7.0.0.11-ga-20191216"
    $ sudo dpkg -i nv-tensorrt-repo-${os}-${tag}_1-1_amd64.deb
    $ sudo apt-key add /var/nv-tensorrt-repo-${tag}/7fa2af80.pub
    $ sudo apt update
    $ sudo apt upgrade -y
    $ sudo apt install tensorrt
    $ sudo apt-get install python3-libnvinfer-dev
    $ sudo apt-get install uff-converter-tf

Install Onnx
    
    $ git clone https://github.com/NVIDIA/TensorRT.git
    $ cd TensorRT/tools/onnx-graphsurgeon/
    $ make build
    $ python -m pip install onnx_graphsurgeon-X.Y.Z-py2.py3-none-any.whl --user

where `X, Y, Z` if the vertion number.

Verify the installation.

    $ dpkg -l | grep TensorRT

Install TensorRT python

    $ pip install nvidia-pyindex
    $ pip install nvidia-tensorrt

Install Pycuda

    $ conda activate M
    $ arch=$(uname -m)
    $ folder=${HOME}/src
    $ mkdir -p $folder
    $ sudo apt-get install -y build-essential python3-dev
    $ sudo apt-get install -y libboost-python-dev libboost-thread-dev
    $ sudo /home/m/.conda/envs/M/bin/pip install setuptools==41.0.0
    $ boost_pylib=$(basename /usr/lib/${arch}-linux-gnu/libboost_python*-py3?.so)
    $ boost_pylibname=${boost_pylib%.so}
    $ boost_pyname=${boost_pylibname/lib/}
    $ pushd $folder
    $ wget https://files.pythonhosted.org/packages/5e/3f/5658c38579b41866ba21ee1b5020b8225cec86fe717e4b1c5c972de0a33c/pycuda-2019.1.2.tar.gz
    $ CPU_CORES=$(nproc)
    $ tar xzvf pycuda-2019.1.2.tar.gz
    $ cd pycuda-2019.1.2
    $ sudo /home/m/.conda/envs/M/bin/python ./configure.py --python-exe=/home/m/.conda/envs/M/bin/python --cuda-root=/usr/local/cuda --cudadrv-lib-dir=/usr/lib/${arch}-linux-gnu --boost-inc-dir=/usr/include --boost-lib-dir=/usr/lib/${arch}-linux-gnu --boost-python-libname=${boost_pyname} --boost-thread-libname=boost_thread
    $ make -j$CPU_CORES
    $ sudo /home/m/.conda/envs/M/bin/python setup.py build
    $ sudo /home/m/.conda/envs/M/bin/python setup.py install
    $ popd
    $ sudo /home/m/.conda/envs/M/bin/python -c "import pycuda; print('pycuda version:', pycuda.VERSION)"




## Install Anaconda

**[Access]**
    
    https://www.anaconda.com/products/individual

**[Install]**

    sudo sh Anaconda3-2019.10-Linux-x86_64.sh
    cat >> ~/.bashrc << 'EOF' export PATH=$HOME/anaconda3/bin:${PATH} 'EOF'
    source ~/.bashrc
    conda upgrade -y --all

## Install Pip

    sudo apt install python3-pip -y
