[**SOURCE**](https://www.geeksforgeeks.org/tag/linux-command/)

# [Encrypt/Decrypt Files in Linux using Ccrypt](https://www.geeksforgeeks.org/encrypt-decrypt-files-in-linux-using-ccrypt/)

Ccrypt is a command line tool for encryption and decryption of data. Ccrypt is based on the Rijndael cipher, the same cipher used in the AES standard. On the other hand, in the AES standard, a 128-bit block size is used, whereas ccrypt uses a 256-bit block size. Ccrypt commonly uses the .cpt file extension for encrypted files.

1. Installation

       $ sudo apt-get install ccrypt

# [Basic Linux Commands for day to day life](https://www.geeksforgeeks.org/basic-linux-commands-day-day-life/)

1. `ls`: list a folder’s contents.

       $ ls
       >> add_opencv_to_visual_studio_2019_project.md  hive_sample.txt         Install_new_linux.md  linux-command-GeeksforGeeks.md  Minh_cho.md      m_yolov4-tensorrt.txt  plugins  README.md          serial_number          test-cam-gui
       >> Error_orcuring_when_install_jetson_nano.md   install_hadoop_hive.md  install_SMB.md        linux_command.md                mxnet_server.md  note_gstreamer.txt     qt.conf  reference_FAS.txt  serial_number_nano.py

1. `man`: (manual) learn about options and arguments to be used in any command in Linux.

       man [linux_command]

   Example:

       $ man ls
       $ man nano

1. `apropos`:

       apropos [linux_command]

   Example:

       $ apropos rename
       >> ...
       >> mv (1)               - move (rename) files
       >> prename (1)          - renames multiple files 
       >> rename (2)           - change the name or location of a file
       >> ...

1. `mv`: move or rename files.

       $ mv oldname newname

   as a safe-guard - prevent from overwrite an existing file, always use `-i` option when issuing mv like this.
    
       $ mv -i oldname newname

1. `mkdir`: create a subdirectory in your current working directory

       $ mkdir my_folder

   create a subdirectory (say the directory bar) inside another directory (say the directory foo, 
    
       $ mkdir -p ~/foo/bar

1. `cat`: display the contents of a file.

       $ cat myspeech.txt
       >> Friends, Coders, Linux-lovers!
       >> This is an article in GeeksForGeeks.

1. `less`: just view the last few lines of the file.

       $ less myspeech.txt

# [Daily life Linux Commands](https://www.geeksforgeeks.org/daily-life-linux-commands/)

1. **_Shortcut to Directories_**: You can create a shortcut to frequently accessed directories by adding them to the CDPATH environment variable.

       $ export CDPATH=$CDPATH:/home/m/

1. Cursor Movement Control

    |Control|Description|
    |:---:|---|
    |`Ctrl` + `a`|Move cursor to the start of a line|
    |`Ctrl` + `e`|Move cursor to the end of a line|
    |`Ctrl` + `◁` \ `▷`|Navigate word by word|
    |`Ctrl` + `w`|Delete the whole word to the left of the cursor|
    |`Ctrl` + `k`|Erase to end of line|
    |`Ctrl` + `u`|Erase to beginning of line|

1. **_`tee` - Duplicate pipe content_**:

   `tee` is a very useful utility that append data to multiple existing files at once.
   
       $ tee M.log M2.log M3.log

1. **_`basename`_**:

   Strips directory and suffix from filenames.

       $ basename /mnt/189633FC5A809F41/6464.txt
       >> 6464.txt

1. **_`ps` - Process Status_**: viewing information related with the processes on a system.

    |Command|Description|
    |:---:|---|
    |`ps`|shows the processes for the current shell|
    |`ps -A` \ `ps -e`|view all the running processes|


1. **_`grep`_**: grep searches files for a given character string or pattern and can replace the string with another. This is one method of searching for files within Linux. 

       grep [option(s)] pattern [file(s)]

   Example:
       
       $ grep 'Linux' file1 file2 file3

# [Some useful Linux Hacks](https://www.geeksforgeeks.org/some-useful-linux-hacks/)

1. Sharing Server

       $ python -m http.server 9000

1. **_Increase Speaker Volume_**: Increase the maximum volume of your speakers to a certain percentage.

       $ pactl set-sink-volume 0 80%

1. **_Fortune Messages_**: Make your terminal output you random fortune messages.

    - install `fortune`

          $ sudo apt-get install fortune

    - run

          $ fortune

1. **_Alias command_**:

    - define all alias to your `.bashrc`

          alias sudo='sudo '
          alias pythonM='/home/m/.conda/envs/M/bin/python'
          alias pipM='/home/m/.conda/envs/M/bin/pip'

1. **_Download accelerator Axel_**.

    - Axel accelerates HTTP and FTP downloads by using multiple connection to retrieve files from the destination.
    - install `axel`

          $ sudo apt-get install axel

    - [Reference](https://www.tecmint.com/axel-commandline-download-accelerator-for-linux/)

1. **_Current Weather_**: What about the knowing the current weather of any city around the world.

       $ curl http://wttr.in/Hanoi

