# Git

## Submodule

### Add a Git Submodule

   ```bash
   git submodule add <remote_url> <destination_folder>
   git commit -m "Added the submodule to the project."
   git push
   ```

### Pull a Git Submodule

   ```bash
   git submodule update --init --recursive
   ```

### Update a Git Submodule

   ```bash
   git submodule update --remote --merge
   ```

### Fetch new submodule commits

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

### Remove Git submodules

   ```bash
   $ git submodule deinit <submodule>
   $ git rm <submodule>
   ```

## Add remote

```bash
git remote add origin <remote_url>
git branch -M main
git push -u origin main
```

```bash
git remote add upstream <remote_url>
git fetch upstream
git rebase upstream/main
git push origin
```

```bash
git remote -v
```

```bash
git remote rm <remote_name>
```
