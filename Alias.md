```bash
alias get_ngrok="curl -s http://localhost:4040/api/tunnels | python3 -c \"import json, sys, os, pwd; username=pwd.getpwuid(os.getuid()).pw_name; print(json.load(sys.stdin)['tunnels'][0]['public_url'].replace('tcp://', f'ssh {username}@').replace(':', ' -p '))\""
alias share="python3 -m http.server"

alias hc="history | cut -c 8- | sort | uniq | fzf | tr -d '\\n' | DISPLAY=:0 xclip -selection c"
alias h="history | cut -c 8- | sort | uniq | fzf"

alias notify_done0="notify-send 'DONE' && aplay /usr/share/sounds/sound-icons/canary-long.wav /usr/share/sounds/sound-icons/trumpet-12.wav"
alias notify_done1="notify-send 'DONE' && aplay /usr/share/sounds/sound-icons/canary-long.wav"
alias notify_done2="notify-send 'DONE' && aplay /usr/share/sounds/sound-icons/trumpet-12.wav"
```

For Raspberry Pi
```
alias cap="raspistill -o ~/Pictures/$(date +'%Y%m%d_%H%M%S_%N').jpg"
```
