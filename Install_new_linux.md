[REFERENCE](https://towardsdatascience.com/a-definitive-guide-for-setting-up-a-deep-learning-workstation-with-ubuntu-18-04-5459d70e19c3)

## Install `htop`

    sudo apt install cmake htop tree
    sudo apt-get update
    sudo apt-get --assume-yes upgrade
    sudo apt-get --assume-yes install tmux build-essential gcc g++ make binutils
    sudo apt-get --assume-yes install software-properties-common
    sudo apt-get --assume-yes install git

## Install `openssh`
    
    sudo apt install openssh-server openssh-client

## Install TeamVier

    sudo apt update -y && sudo apt upgrade -y
    wget https://download.teamviewer.com/download/linux/teamviewer_amd64.deb
    sudo apt install ./teamviewer_amd64.deb

## Install `Skype`

    wget https://go.skype.com/skypeforlinux-64.deb
    sudo apt install ./skypeforlinux-64.deb

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
