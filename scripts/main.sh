#!/bin/bash
set -e

# 1. Setup Repository and Autostart
cd /opt
CERT="/opt/certification"
[[ -d $CERT ]] || git clone https://github.com/yaakovEntin/certification.git -b edge-ai
ln -sf ${CERT}/scripts/cert/test.stop /usr/bin/stop

AUTOSTART_LINE='[[ -f /opt/certification/scripts/cert/test.autostart ]] && /opt/certification/scripts/cert/test.autostart'
grep -qxF "$AUTOSTART_LINE" /home/compulab/.profile || echo "$AUTOSTART_LINE" >> /home/compulab/.profile

# 2. Auto-login Configuration
SERVICE_FILE="/lib/systemd/system/serial-getty@.service"
sed -i "s|^ExecStart=.*|ExecStart=-/sbin/agetty -o '-p -- \\\\u' -a compulab --keep-baud 115200,38400,9600 %I \$TERM|" $SERVICE_FILE

# Remove password and elevate compulab to UID 0
passwd -d compulab
sed -i 's|^compulab:x:[0-9]\+:[0-9]\+:|compulab:x:0:0:|' /etc/passwd

WDOG_CONF="/etc/systemd/system.conf"
sed -i 's/.*RuntimeWatchdogSec=.*/RuntimeWatchdogSec=5/' $WDOG_CONF
sed -i 's/.*WatchdogDevice=.*/WatchdogDevice=watchdog0/' $WDOG_CONF
systemctl daemon-reexec

echo "Setup complete"
echo "Read each test's README for connections instructions:"
find $CERT/scripts -name README.md
echo "Run each test's init.sh to initialize it:"
find $CERT/scripts -name init.sh
echo "After that Perform a hard reset to start testing automatically."
