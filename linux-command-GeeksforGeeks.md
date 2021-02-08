[**SOURCE**](https://www.geeksforgeeks.org/tag/linux-command/)

# [SED Command in Linux](https://www.geeksforgeeks.org/sed-command-in-linux-unix-with-examples/)

Sed command in Unix OS can perform a lot of function like searching, find and replace, insertion or deletion.

1. **Syntax**:

      sed OPTIONS... [SCRIPT] [INPUTFILE...] 

1. **Substituting string**

   `s` specifies the substitution operation.

   `/` are delimiters.

   `[nth]` specifies the nth occurences of a pattern in a line. (`empty` means `1`).
   
   `g` specifies all the occurences of a pattern in a line.

   `[line_number]` specifies line number. (`empty` means `all`).

   `$` the last line.

       $ sed 's/[search_pattern]/[replacement_string]/[nth]' [file_name]
       $ sed 's/unix/LINUX/' geekfile.txt
       $ sed 's/unix/LINUX/2' geekfile.txt

       $ sed 's/[search_pattern]/[replacement_string]/g' [file_name]
       $ sed 's/unix/LINUX/g' geekfile.txt

       $ sed 's/[search_pattern]/[replacement_string]/[nth]g' [file_name]
       $ sed 's/unix/LINUX/3g' geekfile.txt

       $ sed '[line_number[,line_number]] s/[search_pattern]/[replacement_string]/[nth]g' [file_name]
       $ sed '[line_number,$] s/[search_pattern]/[replacement_string]/[nth]g' [file_name]
       $ sed '3 s/unix/linux/' geekfile.txt
       $ sed '1,3 s/unix/linux/' geekfile.txt
       $ sed '2,$ s/unix/linux/' geekfile.txt

1. **Replace with re**
       
       $ sed 's/\([re_pattern]\)/\1/[nth]g'
       $ echo "Welcome To The Geek Stuff" | sed 's/\(\b[A-Z]\)/\(\1\)/g'

1. **Duplicating the replaced line**

    `p` specifies duplicating.

    `n` print only the replaced lines

       $ sed [-n] 's/[search_pattern]/[replacement_string]/p' [file_name]
       $ sed 's/unix/linux/p' geekfile.txt
       $ sed -n 's/unix/linux/p' geekfile.txt

1. **Deleting lines from a particular file**

    `d` specifies deleting.

       $ sed '[line_number[,line_number]]d' [file_name]
       $ sed '5d' filename.txt
       $ sed '$d' filename.txt
       $ sed '3,6d' filename.txt
       $ sed '12,$d' filename.txt

       $ sed '/[re_pattern]/d' [file_name]
       $ sed '/abc/d' filename.txt

1. Insert one blank line after each line

       $ sed G M.log

1. Insert two blank lines

       $ sed 'G;G' M.log

1. Delete blank lines and insert one blank line after each line

       $ sed '/^$/d;G' M.log

1. Insert a black line above every line which matches pattern

       $ sed '/love/{x;p;x;}' M.log

1. Insert a black line below every line which matches pattern

       $ sed '/love/G' M.log

1. Insert 4 spaces to the of every lines
       
       $ sed 's/^/    /' M.log

1. Numbering each line of a file (left alignment)

       $ sed =  M.log | sed 'N;s/\n/\t/'

1. Numbering each line of a file (number on left, right-aligned)

       $ sed = M.log | sed 'N; s/^/     /; s/ *\(.\{4,\}\)\n/\1  /'

1. Numbering each line of a file (only if line is not blank)

       $ sed '/./=' M.log | sed '/./N; s/\n/ /'
       

# [Permissions in Linux](https://www.geeksforgeeks.org/permissions-in-linux/)

- e.g `1`:

      $ chmod ugo-rwx [file_name]

- e.g `2`:

      $ chmod ug+rw,o-x [file_name]

- e.g `3`:

      $ chmod ug=rx,o+r [file_name]

- e.g `4`:

      $ chmod ug+rw,o-x [file_name]

- e.g `5`:

      $ chmod ugo+rwx [file_name]
      $ chmod 777 [file_name]

- e.g `6`:

      $ chmod u=r,g=wx,o=rx [file_name]
      $ chmod 435 [file_name] 

- e.g `7`:

      $ chmod ug+rwx,o=rx [file_name]
      $ chmod 775 [file_name]

# [ZIP command in Linux](https://www.geeksforgeeks.org/zip-command-in-linux-with-examples/)

- Compress files in a single `.zip` file
    
      $ zip [options] zipfile.zip  files  list

- Extract files from a `.zip` file

      $ unzip myfile.zip

   |Options|Description|
   |:---:|---|
   |`-d`|Removes the file from the zip archive|
   |`-u`|Update the specified list of files or add new files to the existing zip file|
   |`-m`|Deletes the original files after zipping|
   |`-r`|Zip a directory recursively|
   |`-x`|Exclude the files in creating the zip|
   |`-v`|Verbose mode|

# [TAR command in Linux](https://www.geeksforgeeks.org/tar-command-linux-examples/?ref=lbp)

    tar [options] [archive-file] [file or directory to be archived]

|Options|Description|
|:---:|---|
|`-c`|Creates Archive|
|`-x`|Extract the archive|
|`-f`|creates archive with given filename|
|`-t`|displays or lists files in archived file|
|`-u`|archives and adds to an existing archive file|
|`-v`|Displays Verbose Information|
|`-A`|Concatenates the archive files|
|`-z`|zip, tells tar command that create tar file using `gzip`|
|`-j`|filter archive tar file using `tbzip`|
|`-W`|Verify a archive file|
|`-r`|update or add file or directory in already existed `.tar` file|

1. Creating an uncompressed `tar` Archive.

       $ tar cvf file.tar *.c

1. Extracting files from Archive

       $ tar xvf file.tar

1. `gzip` compression on the tar Archive

       $ tar cvzf file.tar.gz *.c

1. Extracting a gzip tar Archive `*.tar.gz`

       $ tar xvzf file.tar.gz

1. Creating compressed tar archive file in Linux

       $ tar cvfj file.tar.tbz example.cpp

1. Update existing tar file in Linux

       $ tar rvf file.tar *.c

1. Viewing the Archive

       $ tar tvf file.tar
       >> -rwxrwxrwx root/root       191 2017-09-17 02:20 os2.c
       >> -rwxrwxrwx root/root       218 2017-09-17 02:20 os3.c
       >> -rwxrwxrwx root/root       493 2017-09-17 02:20 os4.c

# [`IPCS` command in Linux with examples](https://www.geeksforgeeks.org/ipcs-command-linux-examples/)

`ipcs` shows information on the inter-process communication facilities for which the calling process has read access. By default, it shows information about all three resources: shared memory segments, message queues, and semaphore arrays.
Without options, the information shall be written in short format for message queues, shared memory segments, and semaphore sets that are currently active in the system. Otherwise, the information that is displayed is controlled by the options specified.

# [`dd` command in Linux](https://www.geeksforgeeks.org/dd-command-linux/)

Safely and reliably make perfect copies of drives, partitions, and filesystems with the Linux dd tool. Whether you're trying to rescue data from a dying storage drive, backing up archives to remote storage, or making a perfect copy of an active partition somewhere else, you'll need to know how to safely and reliably copy drives and filesystems.

1. Backup the entire hard disk

- To backup an entire copy of a hard disk to another hard disk connected to the same system, execute the `dd` command as shown. In this dd command example, the UNIX device name of the source hard disk is /dev/hda, and device name of the target hard disk is /dev/hdb. 

      $ dd if = /dev/sda of = /dev/sdb

1. Backup a Partition

      $ dd if=/dev/sda1 of=~/partition.img

1. Create an image of a hard disk

      $ dd if=/dev/sda of=~/sdadisk.img

1. Restore using the hard disk image

      $ dd if=hdadisk.img of=/dev/hdb

1. To create CDROM backup

      $ dd if=/dev/cdrom of=tgsservice.iso bs=2048

# [*Soft Link* And *Hard Link* In Linux](https://ostechnix.com/explaining-soft-link-and-hard-link-in-linux-with-examples/#:~:text=What%20is%20Soft%20Link%20And,to%20a%20non%2Dexistent%20file)

- A `symbolic` or `soft link` is an actual link to the original file. If you delete the original file, the soft link has no value, because it points to a non-existent file.

      $ ln -s source.file softlink.file

- A `hard link` is a mirror copy of the original file. But hard link, if you delete the original file, the hard link will still has the data of the original file. Because hard link acts as a mirror copy of the original file.

      $ ln source.file hardlink.file

# [`crontab` in Linux](https://www.geeksforgeeks.org/crontab-in-linux-with-examples/)

The crontab is a list of commands that you want to run on a regular schedule.
Linux Crontab format:

    MIN HOUR DOM MON DOW CMD

|Field|Description|Allowed Value|
|:---:|---|---|
|`MIN`|Minute field|`0` to `59`|
|`HOUR`|Hour field|`0` to `23`|
|`DOM`|Day of Month|`1` to `31`|
|`MON`|Month field|`1` to `12`|
|`DOW`|Day Of Week|`0` to `6`|
|`CMD`|Command|Any command to be executed.|

- Using Operators

|Operator|Name|Description|
|:---:|---|---|
|`*`|asterisk|Stands for all values. Use this operator to keep tasks running during all months, or all days of the week.|
|`,`|comma|specifies separate individual values.|
|`-`|dash|Indicates a range of values.|
|`/`|forward-slash|Used to divide a value into steps. (*/2 would be every 2 uints, */3 would be every 3 uint, */10 would be every tenth, etc.)|

- Cron special keywords and its meaning

|Keyword|Equivalent|
|:---:|:---:|
|`@reboot`|Run once after `reboot`.|
|`@yearly`|Run once a year, ie. `0 0 1 1 *`|
|`@annually`|Run once a year, ie. `0 0 1 1 *`|
|`@monthly`|Run once a month, ie. `0 0 1 * *`|
|`@weekly`|Run once a week, ie. `0 0 * * 0`|
|`@daily`|Run once a day, ie. `0 0 * * *`|
|`@hourly`|Run once an hour, ie. `0 * * * *`|


- Common command

|Command|Description|
|:---:|---|
|`crontab -e`|tạo hoặc chỉnh sửa file crontab|
|`crontab -l`|hiển thị file crontab|
|`crontab -r`|xóa file crontab|


# `ls` command

1. List and sort the file by modification time.

       $ ls -t
  
- In Reverse order

      $ ls -tr

1. Display one file per line

       $ ls -1

1. Display all information about files / directories.

       $ ls -l
       >> -rw-rw-r-- 1 m m  7178 Thg 1  3 12:39 Minh_cho.md

   - Field explanation:
       - Field 1 - File permissions
       - Field 2 - Number of links
       - Field 3 - Owner
       - Field 4 - Group
       - Field 5 - Size (in bytes)
       - Field 6 - Last modified date and time
       - Field 7 - File name

   - Display File UID and GID instead username and group name

         $ ls -n
         >> total 164
         >> -rw-rw-r-- 1 1000 1000  1948 Thg 1  3 12:39 add_opencv_to_visual_studio_2019_project.md
         >> -rw-rw-r-- 1 1000 1000 25081 Thg 1  3 12:39 Error_orcuring_when_install_jetson_nano.md
         >> -rw-rw-r-- 1 1000 1000   204 Thg 1  3 12:39 hive_sample.txt
         >> -rw-rw-r-- 1 1000 1000  5099 Thg 1  3 12:39 install_hadoop_hive.md
         >> -rw-rw-r-- 1 1000 1000  8734 Thg 1 11 01:59 Install_new_linux.md


1. Display file size in human readable format

       $ ls -lh
       >> -rw-rw-r-- 1 m m 7,1K Thg 1  3 12:39 Minh_cho.md

1. Display directory information

       $ ls -ld serial_number/
       >> drwxrwxr-x 2 m m 4096 Thg 1  3 12:39 serial_number/

1. Display hidden files

       $ ls -la
       >> total 20
       >> drwxrwxr-x 2 m m 4096 Thg 1  3 12:39 .
       >> drwxrwxr-x 6 m m 4096 Thg 1 11 01:40 ..
       >> drwxrwxr-x 1 m m 2210 Thg 1  3 12:39 folder
       >> -rw-rw-r-- 1 m m 4139 Thg 1  3 12:39 serial_number_nano.py
       >> -rw-rw-r-- 1 m m   64 Thg 1  3 12:39 .unique

       $ ls -lA
       >> total 12
       >> drwxrwxr-x 1 m m 2210 Thg 1  3 12:39 folder
       >> -rw-rw-r-- 1 m m 4139 Thg 1  3 12:39 serial_number_nano.py
       >> -rw-rw-r-- 1 m m   64 Thg 1  3 12:39 .unique

1. Display files recursively

       $ ls -R

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
   |`\|`|Or|`>>> re.findall("anh\|Hien", sentence)`<br>`['Hien', 'anh']`|
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

1. Display a calendar and date of Easter

       $ cal
       $ ncal
