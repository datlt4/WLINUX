# Git

## Submodule

1. Basic Commands Overview

| Command                           | Description                                                |
|------------------------------------|------------------------------------------------------------|
| `git submodule add <repo_url>`     | Add a submodule to your project                            |
| `git submodule init`               | Initialize your submodules                                 |
| `git submodule update`             | Fetch and checkout submodule commits                       |
| `git submodule status`             | Check the status of your submodules                        |
| `git submodule foreach <command>`  | Run a command in each submodule                            |
| `git clone --recurse-submodules`   | Clone a repository and its submodules                      |
| `git submodule sync`               | Sync submodule URLs when they change                       |
| `git push`                         | Push changes in the main project and submodule (if updated)|

1. Add a Git Submodule

   ```bash
   git submodule add <remote_url> <destination_folder>
   git commit -m "Added the submodule to the project."
   git push
   ```

2. Pull a Git Submodule

   ```bash
   git submodule update --init --recursive
   ```

3. Update a Git Submodule

   ```bash
   git submodule update --remote --merge
   ```

4. Fetch new submodule commits

   ```bash
   $ cd <repository>/<submodule>
   $ git fetch

   $ git log --oneline origin/master -3

   93360a2 (origin/master, origin/HEAD) Second commit
   88db523 First commit
   43d0813 (HEAD -> master) Initial commit

   $ git checkout -q 93360a2

   $ cd <repository>
   $ git add .
   $ git commit -m "Added new commits from the submodule repository"
   $ git push
   ```

5. Remove Git submodules

   ```bash
   $ git submodule deinit <submodule>
   $ git rm <submodule>
   ```

## Add remote repo

1. Add
   
   ```bash
   git remote add origin <remote_url>
   git branch -M main
   git push -u origin main
   ```

2. Use
   
   ```bash
   git remote add upstream <remote_url>
   git fetch upstream
   git rebase upstream/main
   git push origin
   ```

3. Check
   
   ```bash
   git remote -v
   ```

4. Remove

   ```bash
   git remote rm <remote_name>
   ```

## Git LFS

### Install package

```bash
sudo apt install git-lfs -y
```

### Initialize

1. Initialize Git LFS in a repository

   ```bash
   git lfs install
   ```

2. Track large files

   ```bash
   git lfs track "*.psd"

   git add .gitattributes
   git commit -m "Track PSD files using Git LFS"
   ```

3. Adding large files to Git

   ```bash
   git add large-file.psd
   git commit -m "Added large PSD file"
   ```

4. Cloning a repository with Git LFS

   ```bash
   git clone https://github.com/username/repo.git
   cd repo
   
   # Pull down all LFS files
   git lfs pull
   ```

5. Fetching and Pulling large files

   ```bash
   git lfs fetch
   git pull
   ```

6. Checking status of LFS files

   ```bash
   git push origin main
   ```

7. Untracking files

   ```bash
   git lfs untrack "*.psd"
   ```

8. Fetching Recent Files

   ```bash
   git lfs fetch --recent
   git lfs fetch --recent <n> # Fetches LFS objects for commits made in the last n days.
   git lfs fetch --recent --recent-refs-days <n>
   git lfs fetch --recent --recent-commits-days 7  # fetches commits from the last 7 days

   # Fetch Specific LFS Files by Pattern (-I and -X)
   # -I Option (Include specific files):
   git lfs fetch -I "path/to/file.txt"
   git lfs fetch -I "*.jpg"
   # -X Option (Exclude specific files):
   git lfs fetch -X "*.png"
   # Combined Example (-I and -X):
   git lfs fetch -I "*.jpg" -X "*.large.jpg"
   ```
