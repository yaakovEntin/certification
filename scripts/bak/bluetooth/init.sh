#!/bin/bash
set -e

apt update && apt install -y bluez-tools bluez-obexd

# Bluetooth Setup (Non-interactive)
bluetoothctl power on
bluetoothctl discoverable on
bluetoothctl pairable on

# Bind to AP - Replace MAC if different for specific units
AP_MAC="A0:D3:65:BD:E1:23"
bluetoothctl scan on &
sleep 5
bluetoothctl pair $AP_MAC
bluetoothctl trust $AP_MAC
bluetoothctl connect $AP_MAC

echo "BT Setup complete."