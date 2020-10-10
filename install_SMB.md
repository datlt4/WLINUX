# Install dependencies

    sudo apt update
    sudo apt install samba -y

# Setting up Samba

    sudo nano /etc/samba/smb.conf

At the bottom of the file, add the following lines:

    [m_folder_name]
        comment = Samba on Ubuntu
        path = /home/m/m_folder_name
        read only = no
        browsable = yes

# Restart Samba
    
    sudo service smbd restart
    sudo ufw allow samba
    sudo smbpasswd -a m

# Connect to Server:

    smb://192.168.1.20/m_folder_name
    port: 139


# Reference

1. [Install and configure Samba](https://ubuntu.com/tutorials/install-and-configure-samba#1-overview)

# Python - HTTP server

    python -m http.server
