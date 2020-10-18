[**SOURCE**](https://www.geeksforgeeks.org/tag/linux-command/)

# Regular Expression

    import re
    sentence = "Nguyen Hien anh - 06/03/1997, you are so beautiful"
    
- Python `re` Library       

   |`re`'s methods|Description|Example|
   |:---:|---|---|
   |`re.match(pattern, string, flags=0)`|_Unknown_|_Unknown_|
   |`re.findall(pattern, string, flags=0)`|Returns a list containing all matches.|`>>> re.findall('n', sentence)`<br>`['n', 'n', 'n']`|
   |`re.search(pattern, string, flags=0)`|Returns A Match object if there is a match anywhere in the string.|`>>> re.search("\s", sentence)`<br>`<_sre.SRE_Match object; span=(6, 7), match=' '>`|
   |`re.split()`|Returns a list where the string has been split at each match.|`>>> re.split("\s", sentence)`<br>`['Nguyen', 'Hien', 'anh', '-', '06/03/1997,', 'you', 'are', 'so', 'beautiful']`<br>`>>> re.split("\s", sentence, 2)`<br>`['Nguyen', 'Hien', 'anh - 06/03/1997, you are so beautiful']`|
   |`re.sub(pattern, repl, string, flags=0)`|Replaces one or many matches with a string.|`>>> re.split("\s", sentence)`<br>`['Nguyen', 'Hien', 'anh', '-', '06/03/1997,', 'you', 'are', 'so', 'beatiful']`|
   |match object|`obj = _sre.SRE_Match` object<br>`obj.span()`: return một tuple (start, stop).<br>`obj.start()`: start position of the match.<br>`obj.stop()`: stop position of the match.<br>`obj.string()`: return the string passed into the function.<br>`obj.group()`: return the part of string where there was a match.||

- `re` pattern

   |`re`'s pattern|Description|Example|
   |:---:|---|---|
   |`[]` (square brackets)|A set of characters.|`>>> re.findall("[a-m]", sentence)`<br>`['g', 'e', 'i', 'e', 'a', 'h', 'a', 'e', 'b', 'e', 'a', 'i', 'f', 'l']`|
   |`.` (Dot)|match bất kỳ ký tự nào ngoại trừ `[\n]`.<br>`re.DOTALL` flag giúp `'.'` match bất kỳ ký tự nào kể cả `[\n]`.|`re.findall('...............', sentence)`<br>`['Nguyen Hien anh', ' - 06/03/1997, ', 'you are so beau']`|
   |`|`|Or|`>>> re.findall("anh|Hien", sentence)`<br>`['Hien', 'anh']`|
   |`*` (Star)|Check xem một string có được theo sau bởi **_0_** hoặc **_n_** ký tự.|`>>> re.findall("en*", 'Nguyen Hiennnn anh - 06/03/1997, you are so beautiful')`<br>`['en', 'ennnn', 'e', 'e']`|
   |`+` (Plus)|Check xem một string có được theo sau bởi **_1_** hoặc **_n_** ký tự.|`>>> re.findall("en+", 'Nguyen Hiennnn anh - 06/03/1997, you are so beautiful')`<br>`['en', 'ennnn']`|
   |`^` (Caret)|Starts with|`>>> re.findall("You are so cute", sentence)`<br>`[]`<br>`>>> re.findall("^Nguyen Hien anh", sentence)`<br>`['Nguyen Hien anh']`|
   |`$`|Ends with|`>>> re.findall("ful$", sentence)`<br>`['ful']`|
   |`{}`|Check xem một string được theo sau bởi `{#}` ký tự<br>`{#}`<br>`{#,}`<br>`{#,#}`|`>>> re.findall("en{1}", 'Nguyen Hiennnn anh - 0`>>> re.findall("anh|Hien", sentence)`<br>`['Hien', 'anh']`6/03/1997, you are so beautiful')`<br>`['en', 'en']`<br>`>>> re.findall('en{1,}', "Nguyen Hiennnnn anh - 06/03/1997, you are so beautiful")`<br>`['en', 'ennnnn']`<br>`>>> re.findall('en{1,3}', "Nguyen Hiennnnn anh - 06/03/1997, you are so beautiful")`<br>`['en', 'ennn']`<br>|

- Escape characters

   |`re`'s escape characters|Description|Example|
   |:---:|---|---|
   |`r"\A"`|**_Starts with_**|`>>> re.findall("\AI", sentence)`<br>`[]`<br>`>>> re.findall("\ANguyen", sentence)`<br>`['Nguyen']`|
   |`r"\b"`|Check xem một match có được bắt đầu hoặc kết thúc bởi các ký tự xác định|`>>> re.findall(r"en\b", sentence)`<br>`['en', 'en']`<br>`>>> re.findall(r"\bNg", sentence)`<br>`['Ng']`<br>`>>> re.findall(r"ie\b", sentence)`<br>`[]`|
   |`r"\B"`|Check xem một match có xuất hiện nhưng **KHÔNG** phải bắt đầu hoặc kết thúc.|`>>> re.findall(r"e\B", sentence)`<br>`['e', 'e']`<br>`>>> re.findall(r"\Be", sentence)`<br>`['e', 'e', 'e']`|
   |`r"\d"`|Return 1 match chứa string chứa các số từ `0-9`|`>>> re.findall(r"\d", sentence)`<br>`['0', '6', '0', '3', '1', '9', '9', '7']`|
   |`r"\D"`|Return 1 match chứa string **KHÔNG** có các số từ `0-9`|`>>> re.findall(r"\D", sentence)`<br>`['N', 'g', 'u', 'y', 'e', 'n', ' ', 'H', 'i', 'e', 'n', ' ', 'a', 'n', 'h', ' ', '-', ' ', '/', '/', ',', ' ', 'y', 'o', 'u', ' ', 'a', 'r', 'e', ' ', 's', 'o', ' ', 'b', 'e', 'a', 'u', 't', 'i', 'f', 'u', 'l']`|
   |`r"\s"`|Return 1 match chứa string chứa các ký tự trắng.`"\s"` thay thế cho các ký tự `[space]`, `[tab]`, `[return]`.|`>>> re.findall(r"\s", sentence)`<br>`[' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ']`|
   |`r"\S"`|Return 1 match chứa string **KHÔNG** chứa ký tự trắng.|`>>> re.findall(r"\S", sentence)`<br>`['N', 'g', 'u', 'y', 'e', 'n', 'H', 'i', 'e', 'n', 'a', 'n', 'h', '-', '0', '6', '/', '0', '3', '/', '1', '9', '9', '7', ',', 'y', 'o', 'u', 'a', 'r', 'e', 's', 'o', 'b', 'e', 'a', 'u', 't', 'i', 'f', 'u', 'l']`|
   |`r"\w"`|Return 1 match chứa string chứa ký tự a-z, A-Z, 0-9 và dấu underscore (_).|`>>> re.findall(r"\w", sentence)`<br>`['N', 'g', 'u', 'y', 'e', 'n', 'H', 'i', 'e', 'n', 'a', 'n', 'h', '0', '6', '0', '3', '1', '9', '9', '7', 'y', 'o', 'u', 'a', 'r', 'e', 's', 'o', 'b', 'e', 'a', 'u', 't', 'i', 'f', 'u', 'l']`|
   |`r"\W"`|Return 1 match chứa string chứa ký tự WORD nào.|`>>> re.findall(r"\W", sentence)`<br>`[' ', ' ', ' ', '-', ' ', '/', '/', ',', ' ', ' ', ' ', ' ']`|
   |`r"\Z"`|**_Ends with_**|`>>> re.findall(r"you are so beautiful\Z", sentence)`<br>`['you are so beautiful']`|
   |`r"[ae0]"`|Return 1 match chứa string chứa các ký tự trong class character.|`>>> re.findall(r"[ae0]", sentence)`<br>`['e', 'e', 'a', '0', '0', 'a', 'e', 'e', 'a']`|
   |`r"[a-n]"`|Return 1 match chứa string chứa các ký tự lower case từ `a-n`.|`>>> re.findall(r"[a-n]", sentence)`<br>`['g', 'e', 'n', 'i', 'e', 'n', 'a', 'n', 'h', 'a', 'e', 'b', 'e', 'a', 'f']`|
   |`r"[^NHA]"`|return 1 match chứa các ký tự **_NGOẠI TRỪ_** class character.|`>>> re.findall(r"[^a-s]", sentence)`<br>`['N', 'u', 'y', ' ', 'H', ' ', ' ', '-', ' ', '0', '6', '/', '0', '3', '/', '1', '9', '9', '7', ',', ' ', 'y', 'u', ' ', ' ', ' ', 'u', 't', 'u']`|
   |`r"[0-5][0-9]"`|Return một match từ `00-59`.|`>>> re.findall(r"[0-3][0-9]", sentence)`<br>`['06', '03', '19']`|
   |`r"[0-37-9]"`|class character từ `0-3` or `7-9`.|`>>> re.findall(r"[0-37-9]", sentence)`<br>`['0', '0', '3', '1', '9', '9', '7']`|

# `grep` command in Unix/Linux

- The `grep` filter searches a file for a particular pattern of characters, and displays all lines that contain that pattern. `grep` stands for ***G***lobally search for ***R***egular ***E***xpression and ***P***rint out)

   Syntax:

      grep [options] pattern [files]

   |Options|Description|
   |:---:|---|
   |`-c`|This prints only a count of the lines that match a pattern|
   |`-h`|Display the matched lines, but do not display the filenames.|
   |`-i`|Case insensitive search|
   |`-l`|Displays list of a filenames only.|
   |`-n`|Display the matched lines and their line numbers.|
   |`-v`|This prints out all the lines that do not matches the pattern|
   |`-e` exp|Specifies expression with this option. Can use multiple times.|
   |`-f` file|Takes patterns from file, one per line.|
   |`-E`|Treats pattern as an extended regular expression (ERE)|
   |`-w`|Match whole word|
   |`-o`|Print only the matched parts of a matching line, with each such part on a separate output line.|

- Sample Commands

      $ cat > geekfile.txt

      unix is great os. unix is opensource. unix is free os.
      learn operating system.
      Unix linux which one you choose.
      uNix is easy to learn.unix is a multiuser os.Learn unix .unix is a powerful.

1. **Case insensitive search**

       $ grep -i "UNix" geekfile.txt
       >> `unix` is great os. `unix` is opensource. `unix` is free os.
       >> `Unix` linux which one you choose.
       >> `uNix` is easy to learn.`unix` is a multiuser os.Learn `unix` .`unix` is a powerful.

2. **Count of line number of matches**

       $ grep -c "unix" geekfile.txt
       >> 2

3. **Display the file names that matches the pattern**

       $ grep -l "unix" *
       >> geekfile.txt
       $ grep -l "unix" f1.txt f2.txt f3.xt f4.txt geekfile.txt
       >> geekfile.txt

4. **Checking for the whole words in a file**

       $ grep -w "unix" geekfile.txt
       >> unix is great os. unix is opensource. unix is free os.
       >> uNix is easy to learn.unix is a multiuser os.Learn unix .unix is a powerful.

5. **Displaying only the matched pattern**

       $ grep -o "unix" geekfile.txt
       >> unix
       >> unix
       >> unix
       >> unix
       >> unix
       >> unix

6. **Show line number while displaying the output using grep -n**

       $ grep -n "unix" geekfile.txt
       >> 1:unix is great os. unix is opensource. unix is free os.
       >> 4:uNix is easy to learn.unix is a multiuser os.Learn unix .unix is a powerful.

7. **Inverting the pattern match**

       $ grep -v "unix" geekfile.txt
       >> learn operating system.
       >> Unix linux which one you choose.

8. **Matching the lines that start with a string**

       $ grep "^unix" geekfile.txt
       >> unix is great os. unix is opensource. unix is free os.

9. **Matching the lines that end with a string**

       $ grep "os$" geekfile.txt

# [mindepth and maxdepth in Linux find() command for limiting search to a specific directory.](https://www.geeksforgeeks.org/mindepth-maxdepth-linux-find-command-limiting-search-specific-directory/)

- `find` is a command in Linux to search for files in a directory hierarchy. 

       root@m-K501UX:/home/m# find / -name passwd
       >> /usr/bin/passwd
       >> /usr/share/doc/passwd
       >> /usr/share/bash-completion/completions/passwd
       >> /usr/share/lintian/overrides/passwd
       >> /snap/core18/1885/etc/pam.d/passwd
       >> /snap/core18/1885/etc/passwd
       >> /snap/core18/1885/usr/bin/passwd
       >> /snap/core18/1885/usr/share/bash-completion/completions/passwd
       >> /snap/core18/1885/usr/share/doc/passwd
       >> /snap/core18/1885/usr/share/lintian/overrides/passwd
       >> /snap/core18/1885/var/lib/extrausers/passwd
       >> /etc/cron.daily/passwd
       >> /etc/pam.d/passwd
       >> /etc/passwd

- Find the passwd file under root and one level down. (i.e root:level 1, and one sub-directory:level 2)

       root@m-K501UX:/home/m# find / -maxdepth 3 -name passwd
       >> /usr/bin/passwd
       >> /etc/cron.daily/passwd
       >> /etc/pam.d/passwd
       >> /etc/passwd

- Find the password file between sub-directory level 2 and 4.

       root@m-K501UX:/home/m# find / -mindepth 3 -maxdepth 4 -name passwd
       >> /usr/bin/passwd
       >> /usr/share/doc/passwd
       >> /etc/cron.daily/passwd
       >> /etc/pam.d/passwd  

# [Encrypt / Decrypt Files in Linux using Ccrypt](https://www.geeksforgeeks.org/encrypt-decrypt-files-in-linux-using-ccrypt/)

Ccrypt is a command line tool for encryption and decryption of data. Ccrypt is based on the Rijndael cipher, the same cipher used in the AES standard. On the other hand, in the AES standard, a 128-bit block size is used, whereas ccrypt uses a 256-bit block size. Ccrypt commonly uses the .cpt file extension for encrypted files.

1. Installation

       $ sudo apt-get install ccrypt

1. Options
     
   |Option|Option 2|Description|
   |:---:|:---:|---|
   |`-e`|`--encrypt`|Encrypt|
   |`-d`|`--decrypt`|Decrypt|
   |`-c`|`--cat`|Decrypt one or more files to standard output.|
   |`-x`|`--keychange`|Change the key of encrypted data.|
   |`-u`|`--unixcrypt`|Simulate the old unix crypt command.|

1. Encrypt file

       $ ccrypt M.log
       >> Enter encryption key: 
       >> Enter encryption key: (repeat)
       
1. Decrypt file 

       $ ccrypt -d M.log.cpt 
       >> Enter decryption key:


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

