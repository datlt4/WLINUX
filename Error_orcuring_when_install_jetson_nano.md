# [INFO] Jetson Download Center
Reference:

    1. https://developer.nvidia.com/embedded/downloads
    

# [ERROR] `N: Unable to locate package python-pip`
Reason:

    have to enable universe category which contains python-pip package.

Solution:

    01. sudo apt-get update
    02. sudo apt-get upgrade
    03. sudo apt install nano -y 
    04. sudo apt-get install htop -y
    05. sudo apt-get install tmux -y
    05. sudo apt install python3-pip -y
    06. sudo -H pip3 install jetson-stats
    07. sudo -H pip3 install --upgrade setuptools
    08. sudo -H pip3 install cython
    09. sudo -H pip3 install -U setuptools
    10. sudo nano /etc/apt/sources.list
    11. add universe at the end of file

    # See http://help.ubuntu.com/community/UpgradeNotes for how to upgrade to
    # newer versions of the distribution.
    deb http://ports.ubuntu.com/ubuntu-ports/ bionic main restricted universe
    # deb-src http://ports.ubuntu.com/ubuntu-ports/ bionic main restricted

    ## Major bug fix updates produced after the final release of the
    ## distribution.
    deb http://ports.ubuntu.com/ubuntu-ports/ bionic-updates main restricted universe
    # deb-src http://ports.ubuntu.com/ubuntu-ports/ bionic-updates main restricted

    ## N.B. software from this repository is ENTIRELY UNSUPPORTED by the Ubuntu
    ## team. Also, please note that software in universe WILL NOT receive any
    ## review or updates from the Ubuntu security team.
    # deb-src http://ports.ubuntu.com/ubuntu-ports/ bionic universe
    # deb-src http://ports.ubuntu.com/ubuntu-ports/ bionic-updates universe

    ## N.B. software from this repository is ENTIRELY UNSUPPORTED by the Ubuntu
    ## team, and may not be under a free licence. Please satisfy yourself as to
    ## your rights to use the software. Also, please note that software in
    ## multiverse WILL NOT receive any review or updates from the Ubuntu
    ## security team.
    deb http://ports.ubuntu.com/ubuntu-ports/ bionic multiverse
    # deb-src http://ports.ubuntu.com/ubuntu-ports/ bionic multiverse
    deb http://ports.ubuntu.com/ubuntu-ports/ bionic-updates multiverse
    # deb-src http://ports.ubuntu.com/ubuntu-ports/ bionic-updates multiverse

    ## N.B. software from this repository may not have been tested as
    ## extensively as that contained in the main release, although it includes
    ## newer versions of some applications which may provide useful features.
    ## Also, please note that software in backports WILL NOT receive any review
    ## or updates from the Ubuntu security team.
    deb http://ports.ubuntu.com/ubuntu-ports/ bionic-backports main restricted multiverse universe
    # deb-src http://ports.ubuntu.com/ubuntu-ports/ bionic-backports main restricted universe multiverse

    ## Uncomment the following two lines to add software from Canonical's
    ## 'partner' repository.##
    ## This software is not part of Ubuntu, but is offered by Canonical and the
    ## respective vendors as a service to Ubuntu users.
    deb http://archive.canonical.com/ubuntu bionic partner
    # deb-src http://archive.canonical.com/ubuntu bionic partner

    deb http://ports.ubuntu.com/ubuntu-ports/ bionic-security main restricted universe
    # deb-src http://ports.ubuntu.com/ubuntu-ports/ bionic-security main restricted
    # deb-src http://ports.ubuntu.com/ubuntu-ports/ bionic-security universe
    deb http://ports.ubuntu.com/ubuntu-ports/ bionic-security multiverse
    # deb-src http://ports.ubuntu.com/ubuntu-ports/ bionic-security multiverse

# [ERROR] `E: Unable to locate package nano`
Solution:
    
    snap install nano

# [INFO] Check available camera

    ls -ltrh /dev/video*

# [INFO] Jetson Nano CSI-Camera

    git clone https://github.com/JetsonHacksNano/CSI-Camera.git
    git checkout v2.0

# [ERROR] `W: GPG error`
W: GPG error: http://archive.debian.org/debian jessie-backports InRelease: The following signatures couldn't be verified because the public key is not avail able: NO_PUBKEY 8B48AD6246925553 NO_PUBKEY 7638D0442B90D010
Reason:

    apt is telling us that the following keys are missing: 8B48AD6246925553 and 7638D0442B90D010

Solution:

    sudo apt-key adv --keyserver keyserver.ubuntu.com --recv-keys 8B48AD6246925553
    sudo apt-key adv --keyserver keyserver.ubuntu.com --recv-keys 7638D0442B90D010

# [ERROR] `E: Release file for .../InRelease is expired `
E: Release file for http://archive.debian.org/debian/dists/jessie-backports/InRelease is expired (invalid since 357d 12h 49min 26s). Updates for this repository will not be applied.
Solution:

    add "-o Acquire::Check-Valid-Until=false" into the end of command.
    eg: sudo apt update -o Acquire::Check-Valid-Until=false

# [INFO] Uninstall OpenCV Completely


[ ] Reference

    https://installlion.com/ubuntu/xenial/universe/p/python-opencv/uninstall/index.html

Uninstall just python-opencv

    sudo apt-get remove python-opencv

Uninstall python-opencv and its dependencies

    sudo apt-get remove --auto-remove python-opencv

Purging your config/data too

    sudo apt-get purge --auto-remove python-opencv


