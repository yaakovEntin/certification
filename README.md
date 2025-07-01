A sequence of LED blinks signals each test status with a period of 1 second:
green and blue: success
red and amber: error
There are 3 seconds pause between each sequence

note that it takes about a 1.5 min for the modem to find networks, until then it will be red.

# Setup for tests:
Bluetooth :
on DUT and AP:
apt update
apt install bluez-tools
apt install bluez-obexd
bluetoothctl
In interactive session:
```
power on
discoverable on
pairable on
agent on
```
on DUT:
pair 8C:1D:96:F1:87:C1
trust 8C:1D:96:F1:87:C1

WiFi :
sudo nmcli device wifi connect IOTG-IMX8PLUS-AP password q1w2e3r4 name WifiCon-wlan0 ifname wlan0

Net:
nmcli device set eth0 managed no

Before deployment remove any set -e

# set watchdog
vi /etc/systemd/system.conf
change :
RuntimeWatchdogSec=5
WatchdogDevice=watchdog0
systemctl daemon-reexec

# control
to stop all tests run:
stop

to start all tests run:
ctrl+d

In order to disable cellular test run:
stop
rm /opt/Certification/scripts/scan_cell/.autostart
ctrl+d

to re-enable it:
stop
touch /opt/Certification/scripts/scan_cell/.autostart
ctrl+d

to set modem test that checks sim and scans networks:
ln -snf bak/cell_scan cell
to set modem test that checks that modem's only alive:
ln -snf bak/cell_alive cell

# For development:
ln -s /opt/Certification/scripts/cert/test.stop /usr/bin/stop # setup test stopper

