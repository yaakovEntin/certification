# setup repo
* install ubuntu to the DUT with compulab user
* on DUT run:
```
sudo -i
cd /opt
git clone https://github.com/yaakovEntin/certification.git -b edge-ai
CERT="/opt/certification"
ln -s ${CERT}/scripts/cert/test.stop /usr/bin/stop # setup test stopper
AUTOSTART_SCRIPT="${CERT}/scripts/cert/test.autostart"
cat << eof >> /home/compulab/.profile
[[ -f $AUTOSTART_SCRIPT ]] && $AUTOSTART_SCRIPT
eof
cat /home/compulab/.profile
```
## auto login - skip prompts
`sudo -i`
### username
`vi /lib/systemd/system/serial-getty@.service`
- replace ExecStart with : 
`ExecStart=-/sbin/agetty -o '-p -- \\u' -a compulab --keep-baud 115200,38400,9600 %I $TERM`
### password 
```
passwd -d compulab
vi /etc/passwd # add this line to Set UIO=GID=0 :
```
`compulab:x:0:0::/home/compulab:/bin/bash`
hard reset 
# Setup up for specific interfaces:
connect antennas
## Bluetooth :
on DUT and AP:
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
bind DUT to AP (do for each unit):
```
scan on
pair A0:D3:65:BD:E1:23
trust A0:D3:65:BD:E1:23
connect A0:D3:65:BD:E1:23
```
if connection was established even for few seconds, binding succeeded
## Wifi
`sudo nmcli device wifi connect IOTG-IMX8PLUS-AP password q1w2e3r4 name WifiCon-wlan0 ifname wlan0`
# set watchdog
`vi /etc/systemd/system.conf`
change :
```
RuntimeWatchdogSec=5
WatchdogDevice=watchdog0
```
`systemctl daemon-reexec`
# control
to stop testing run:
`stop`

to restart testing press:
- ctrl+d

In order to disable a test for next run :
```
rm ${CERT}/scripts/scan_cell/.autostart
```
ctrl+d

to enable it for next run :
```
touch ${CERT}/scripts/scan_cell/.autostart
```
ctrl+d

to set modem test that scans networks:
`ln -snf bak/cell_scan cell`
to set modem test that only checks that modem's alive:
`ln -snf bak/cell_alive cell`
