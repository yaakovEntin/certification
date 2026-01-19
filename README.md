# Certification Test Suite

## Overview

A sequence of LED blinks signals each test status with a period of 1 second:
- **Green and blue**: success
- **Red and amber**: error
- **3 seconds pause** between each sequence

> **Note:** Cellular modem takes ~1.5 min to finish scan and to return success status, expect red indicators until then.

---

# Setup

## 1. Install Debian on DUT

Follow the installation guide:
https://mediawiki.compulab.com/w/index.php?title=IOT-LINK:_Debian_Linux:_Installation

## 2. Clone Repository on DUT

```bash
sudo -i
cd /opt
git clone https://github.com/yaakovEntin/certification.git
CERT="/opt/certification"
ln -s ${CERT}/scripts/cert/test.stop /usr/bin/stop
AUTOSTART_SCRIPT="${CERT}/scripts/cert/test.autostart"
cat << eof >> /home/compulab/.profile
[[ -f $AUTOSTART_SCRIPT ]] && $AUTOSTART_SCRIPT
eof
cat /home/compulab/.profile
```

## 3. Auto-login Configuration

### Update Serial Terminal Service
Edit `/lib/systemd/system/serial-getty@.service`:
```
ExecStart=-/sbin/agetty -o '-p -- \\u' -a compulab --keep-baud 115200,38400,9600 %I $TERM
```

### Remove Password Requirement
```bash
passwd -d compulab
```

Edit `/etc/passwd` and ensure this line exists:
```
compulab:x:0:0::/home/compulab:/bin/bash
```

Then **hard reset the DUT**.

---

# Test-Specific Setup

## Bluetooth

### Hardware
- Connect **Antenna B** to the Bluetooth module

### Software (on both DUT and AP)
```bash
apt update
apt install bluez-tools bluez-obexd
```

### Initial Pairing (DUT)
```bash
bluetoothctl
[bluetooth]# power on
[bluetooth]# discoverable on
[bluetooth]# pairable on
[bluetooth]# agent on
[bluetooth]# pair 8C:1D:96:F1:87:C1
[bluetooth]# trust 8C:1D:96:F1:87:C1
[bluetooth]# connect 8C:1D:96:F1:87:C1
[bluetooth]# quit
```

## WiFi

```bash
sudo nmcli device wifi connect IOTG-IMX8PLUS-AP password q1w2e3r4 name WifiCon-wlan0 ifname wlan0
```

## Ethernet

- **Connect cable to ETH1 (not ETH2)** on AP
- Verify connection: `ip addr show eth1` should show `state UP`

```bash
nmcli device set eth0 managed no
```

## Cellular Modem

Automatic detection supports:
- Telit LE910C4-WWXD (1bc7:1031)
- Telit FN990 (1bc7:1070)
- Qualcomm S7672

Uses ModemManager for AT port detection when available.

---

# Watchdog Configuration

Edit `/etc/systemd/system.conf`:
```
RuntimeWatchdogSec=5
WatchdogDevice=watchdog0
```

Apply changes:
```bash
systemctl daemon-reexec
```

---

# Test Control

## Stop All Tests
```bash
stop
```

## Restart Tests
Press: `Ctrl+D`

## Enable/Disable Cellular Test

**Disable:**
```bash
stop
rm ${CERT}/scripts/cell/.autostart
Ctrl+D
```

**Enable:**
```bash
stop
touch ${CERT}/scripts/cell/.autostart
Ctrl+D
```

## Switch Cellular Test Mode

**Check SIM + Scan Networks:**
```bash
ln -snf bak/cell_scan cell
```

**Check Modem Alive Only:**
```bash
ln -snf bak/cell_alive cell
```

---

# Troubleshooting

## Bluetooth bt-obex Assertion Error
**Error:**
```
ERROR:lib/bluez/device.c:265:device_get_address: assertion failed
```

**Solution:**
1. Connect Antenna B to Bluetooth module
2. Establish initial pairing/connection before running tests
3. Use `bluetoothctl` to manually pair and connect first

## Ethernet Test Fails
**Check:**
- Cable connected to **ETH1** (not ETH2) on AP
- Both DUT and AP have IPs in 10.50.0.0/24 subnet
- Link is UP: `ip addr show eth1`

---

# Pre-Deployment Checklist

- [ ] Remove any `set -e` from scripts
- [ ] Verify antennas connected (Bluetooth: Antenna B)
- [ ] Test ethernet on ETH1 (not ETH2)
- [ ] Perform initial Bluetooth pairing
- [ ] Configure watchdog
- [ ] Verify auto-login works
