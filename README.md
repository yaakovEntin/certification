* Get AP running
* connect antennas on DUT
* run:
```
bash -e <(curl -sL https://raw.githubusercontent.com/yaakovEntin/certification/refs/heads/edge-ai/scripts/main.sh)
```

# setup Bluetooth
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

# Management Cheat Sheet

| **Task**              | **Command**                                             |
| --------------------- | ------------------------------------------------------- |
| **Stop Testing**      | `stop`                                                  |
| **Restart Testing**   | Press `Ctrl+D`                                          |
| **Disable Cell Scan** | `rm /opt/certification/scripts/scan_cell/.autostart`    |
| **Enable Cell Scan**  | `touch /opt/certification/scripts/scan_cell/.autostart` |
| **Set: Network Scan** | `ln -snf bak/cell_scan /opt/certification/cell`         |
| **Set: Alive Check**  | `ln -snf bak/cell_alive /opt/certification/cell`        |
