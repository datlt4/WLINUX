prerequisite
```
sudo apt install fzf xclip -y
```

```bash
alias get_ngrok="curl -s http://localhost:4040/api/tunnels | python3 -c \"import json, sys, os, pwd; username=pwd.getpwuid(os.getuid()).pw_name; print(json.load(sys.stdin)['tunnels'][0]['public_url'].replace('tcp://', f'ssh {username}@').replace(':', ' -p '))\""
alias share="python3 -m http.server"

alias hc="cat ~/.bash_history -n | cut -c 8- | sort | uniq | fzf | tr -d '\\n' | DISPLAY=:0 xclip -selection c"
alias h="cat ~/.bash_history -n | cut -c 8- | sort | uniq | fzf"
alias H="cat ~/.bash_history -n | cut -c 8- | sort | uniq | fzf"
alias rr="readlink -f"

alias notify_done0="notify-send 'DONE' && aplay /usr/share/sounds/sound-icons/canary-long.wav /usr/share/sounds/sound-icons/trumpet-12.wav"
alias notify_done1="notify-send 'DONE' && aplay /usr/share/sounds/sound-icons/canary-long.wav"
alias notify_done2="notify-send 'DONE' && aplay /usr/share/sounds/sound-icons/trumpet-12.wav"
```

For Raspberry Pi

```bash
alias cap="raspistill -o ~/Pictures/\$(date +%Y%m%d_%H%M%S_%N).jpg"
```

PATH

```bash
export EDITOR="/bin/nano"
export SHELL='/bin/bash'
export PATH=/usr/local/cuda/bin${PATH:+:${PATH}}
export LD_LIBRARY_PATH="/usr/local/cuda/lib64:/usr/local/cuda-11.1/lib64:/usr/local/cuda-11.2/lib64:/usr/local/TensorRT/lib${LD_LIBRARY_PATH:+:${LD_LIBRARY_PATH}}"
export Torch_DIR=/usr/local/lib/python3.8/dist-packages/torch
```

Modify `PS1`

```bash
export PS1="\[\[\033[01;41m\]\u\[\033[00m\]:\[\033[01;32m\]\W \[\033[01;36m\]➔ \[\033[00m\]"
```
