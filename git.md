# Git

## Submodule

```bash
git submodule add <remote_url> <destination_folder>
git commit -m "Added the submodule to the project."
git push
```

## Update submodule

```
git clone --recursive <remote_url> <destination_folder>
```

```bash
git submodule update --init --recursive
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
