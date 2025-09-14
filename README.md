A sequence of LED blinks signals each test status with a period of 1 second:
- green and blue: success
- red and amber: error
There are 3 seconds pause between each sequence

note that it takes about a 1.5 min for the modem to find networks, until then it will be red.
# setup repo
* install Debian to the DUT:
https://mediawiki.compulab.com/w/index.php?title=IOT-LINK:_Debian_Linux:_Installation 
* on DUT run:
```
sudo -i
cd /opt
git clone https://github.com/yaakovEntin/certification.git
CERT="/opt/certification"
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
vi /etc/passwd # must have this line for the user to Set UIO=GID=0 :
```
`compulab:x:0:0::/home/compulab:/bin/bash`
hard reset 
```
ln -s ${CERT}/scripts/cert/test.stop /usr/bin/stop # setup test stopper
```
# Setup up for specific tests:
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
agent on
```
on DUT:
```
pair 8C:1D:96:F1:87:C1
trust 8C:1D:96:F1:87:C1
```
## Wifi
`sudo nmcli device wifi connect IOTG-IMX8PLUS-AP password q1w2e3r4 name WifiCon-wlan0 ifname wlan0`
## Net
`nmcli device set eth0 managed no`

Before deployment remove any set -e
# set watchdog
`vi /etc/systemd/system.conf`
change :
```
RuntimeWatchdogSec=5
WatchdogDevice=watchdog0
```
`systemctl daemon-reexec`
# control
to stop all tests run:
`stop`

to restart tests press:
- ctrl+d

In order to disable cellular test run:
```
stop
rm ${CERT}/scripts/scan_cell/.autostart
```
ctrl+d

to re-enable it:
```
stop
touch ${CERT}/scripts/scan_cell/.autostart
```
ctrl+d

to set modem test that checks sim and scans networks:
`ln -snf bak/cell_scan cell`
to set modem test that checks that modem's only alive:
`ln -snf bak/cell_alive cell`
