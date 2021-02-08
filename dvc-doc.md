# Getting Started

Khởi tạo DVC bên trong một Git project:

    $ dvc init

Các tính năng của DVC được chia thành các nhóm:

1. **_Data versioning (Git for data):_** is the core part of DVC for large files, datasets, machine learning models versioning without storing large files with Git. Think.

1. **_Data access:_** this can help to download a specific version of an ML model to a deployment server or import a model to another project.

1. **_Data pipelines (Makefiles for data and ML projects):_** describe how models and other data artifacts are built, and provide an efficient way to reproduce them.

1. **_Experiments (Git for machine learning):_** attach parameters, metrics, plots. You can capture and navigate experiments without leaving Git.

## Data Versioning
The foundation of DVC consists of a few commands that you can run along with `git` to track large files, directories, or ML models.

1. Firstly

       $ git init
       $ dvc init

1. Add files / folders into the repository.

       $ dvc add [file1] ... [directory1] ...
       $ git add [file1.dvc] ... [directory1.dvc] ... [directory1/.gitignore] ...
       $ git commit -m "Add raw data"

1. Storing and sharing

       $ dvc remote add [option] [name] [url]
       $ git commit .dvc/config -m "Configure remote storage"

    |**Options:**||Description|
    |:---:|:---:|---|
    |`--global`||lưu remote configuration vào global config (`~/.config/dvc/config`) thay vì `.dvc/config`|
    |`--system`||lưu remote configuration vào system config (`/etc/dvc/config`) thay vì `.dvc/config`|
    |`--local`||lưu remote configuration vào local config file (`.dvc/config.local`) thay vì `.dvc/config`|
    |`--default`|`-d`||
    |`--force`|`-f`|ghi đè với `url` mới|
    |`--help`|`-h`|help message|
    |`--quite`|`-q`|im lặng, trả về 0 nếu không có lỗi, 1 là ngược lại|
    |`--verbose`|`-v`|tracing information|

- [**_Supported Storage types_**](https://dvc.org/doc/command-reference/remote/add)

    |Amazon S3|S3 compatible API|Azure Blob Storage|Google Drive|Google Cloud Storage|ALiyun OSS|SSH|HDFS|HTTP|WebDAV|local remote|
    |:---:|:---:|:---:|:---:|:---:|:---:|:---:|:---:|:---:|:---:|:---:|:---:|
    
    - **_SSH_**
          
          $ dvc remote add -d [name_remote] ssh://[user]@[example.com]/path/to/dir

    - **_HTTP_**

          $ dvc remote add -d [name_remote] [https://example.com]/path/to/dir

    - **_Local storage_**

          $ dvc remote add -d [name_remote] /path/to/my-dvc-storage
    
    - **_Google Drive_**
        
          link: https://drive.google.com/drive/u/0/folders/[token]
          $ dvc remote add -d myremote gdrive://[token]

## Data Access
How can we use these artifacts outside of the project? How do I download a model to deploy it? How do I download a specific version of a model? How do I reuse datasets across different projects?

1. Find a file or directory

       $ dvc list [Git repository link]

2. Download a file or directory

       $ dvc get [Git repository link] [filename / foldername] [-o newname]

3. Import a file or directory

       $ dvc import [Git repository link] [filename / foldername] [-o newname]