prerequisite
```
sudo apt install fzf xclip -y
```

```bash
figlet REMEMBER TO BACKUP DATA

alias get_ngrok="curl -s http://localhost:4040/api/tunnels | python3 -c \"import json, sys, os, pwd; username=pwd.getpwuid(os.getuid()).pw_name; print(json.load(sys.stdin)['tunnels'][0]['public_url'].replace('tcp://', f'ssh {username}@').replace(':', ' -p '))\""
alias share="python3 -m http.server"

alias hc="cat ~/.bash_history -n | cut -c 8- | sort | uniq | fzf | tr -d '\\n' | DISPLAY=:0 xclip -selection c"
alias h="cat ~/.bash_history -n | cut -c 8- | sort | uniq | fzf"
alias H="cat ~/.bash_history -n | cut -c 8- | sort | uniq | fzf"
alias rr="readlink -f"
alias rrc="readlink -f * | sort | uniq | fzf | tr -d '\\n' | DISPLAY=:0 xclip -selection c"
alias pwdc="pwd | tr -d '\\n' | DISPLAY=:0 xclip -selection c"

alias buzz0="notify-send 'DONE' && aplay /usr/share/sounds/sound-icons/canary-long.wav /usr/share/sounds/sound-icons/trumpet-12.wav"
alias buzz1="notify-send 'DONE' && aplay /usr/share/sounds/sound-icons/canary-long.wav"
alias buzz2="notify-send 'DONE' && aplay /usr/share/sounds/sound-icons/trumpet-12.wav"

alias doc="cd /home/emoi/Documents"
alias dl="cd /home/emoi/Downloads"
alias b="cd build"
alias .-="cd -"
alias ..="cd ../"
alias ...="cd ../../"
alias ....="cd ../../../"

alias open_vpn="/usr/bin/openvpn3 session-start --config <PATH_TO_OVPN_FILE>.ovpn"
stop_vpn() {
     /usr/bin/openvpn3 session-manage --session-path $(openvpn3 sessions-list | grep -B 4 '<FILE NAME>.ovpn' | grep 'Path:' | awk '{print $2}') --disconnect
}
alias docker_nvidia="xhost +local:root && docker run -it --rm --net=host --runtime nvidia --gpus all -v /tmp/.X11-unix/:/tmp/.X11-unix -v ${HOME}/.Xauthority:/root/.Xauthority --device /dev/dri:/dev/dri -e DISPLAY=$DISPLAY"

alias hack_wintel="sudo sysctl -w net.ipv4.ip_default_ttl=65"
alias LocalSend="cd /mnt/ssd_1tb/Downloads-Ubuntu/Miscellaneous && ./LocalSend-1.16.1-linux-x86-64.AppImage"
alias k="--profile koi_1"
alias cursor="$(ls -1t ~/Downloads/Cursor-* | head -n 1)"
alias rnote="flatpak run com.github.flxzt.rnote"
alias own="sudo chown -R koi:koi"
```

For Raspberry Pi

```bash
alias cap="raspistill -o ~/Pictures/\$(date +%Y%m%d_%H%M%S_%N).jpg"
```

Get temporature Raspberry Pi

```bash
echo "CPU: $(printf %.1f $(</sys/class/thermal/thermal_zone0/temp)e-3)'C ... GPU: $(/opt/vc/bin/vcgencmd measure_temp | awk -F [=\'] '{print($2)}')'C"
```

PATH

```bash
export EDITOR="/bin/nano"
export SHELL='/bin/bash'
export PATH=/usr/local/cuda/bin:/opt/Qt/6.2.2/gcc_64/lib/cmake:/usr/local/go/bin:${PATH}
export LD_LIBRARY_PATH="/usr/local/cuda/lib64:/usr/local/TensorRT/lib:/usr/local/cuda/extras/CUPTI/lib64:${LD_LIBRARY_PATH}"
export LD_LIBRARY_PATH="/usr/local/lib:${LD_LIBRARY_PATH}"
export Torch_DIR=/usr/local/lib/python3.8/dist-packages/torch
export Qt6Core_DIR=/opt/Qt/6.2.2/gcc_64/lib/cmake/Qt6Core
export Qt6_DIR=/opt/Qt/6.2.2/gcc_64/lib/cmake/Qt6
```

Modify `PS1`

```bash
parse_git_branch() {
     git branch 2> /dev/null | sed -e '/^[^*]/d' -e 's/* \(.*\)/(\1)/'
}
parse_git_branch2() {
     git config --global --add safe.directory $(pwd)
     if [[ $(parse_git_branch) ]]; then
          echo "git:"
     else
          echo ""
     fi
}
export PS1="\[\[\033[01;43m\]\u\[\033[00m\]:\[\033[01;32m\]\W \[\e[96m\]\$(parse_git_branch2)\[\e[91m\]\$(parse_git_branch)\[\e[00m\]\[\033[01;36m\]➜ \[\033[00m\]"
# For zsh
# export PS1="%n@%m:%1~ $(parse_git_branch2)$(parse_git_branch) ➜ "
```

