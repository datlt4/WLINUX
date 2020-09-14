## Install `htop`

    sudo apt install htop

## Install `tmux`

    sudo apt install tmux

## Install `openssh`
    
    sudo apt install openssh-server openssh-client

## Install TeamVier

    sudo apt update -y && sudo apt upgrade -y
    wget https://download.teamviewer.com/download/linux/teamviewer_amd64.deb
    sudo apt install ./teamviewer_amd64.deb

## Insall `Skype`

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
    ibus-daemon &
    ibus restart

## Install KDE-Plasm

    sudo apt install tasksel
    sudo tasksel install kubuntu-desktop
        - select <OK>
        - select sddm
    sudo apt install sddm
    sudo dpkg-reconfigure sddm


