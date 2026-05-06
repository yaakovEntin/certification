# manual setup
on AP run:
```
apt update
apt install bluez-tools
apt install bluez-obexd
bluetoothctl
```
In interactive session:
```
power on
discoverable on
pairable on
```
if connection was established even for few seconds, binding succeeded
