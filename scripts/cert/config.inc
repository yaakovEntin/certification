#DEBUG=1
export PS4='[$BASH_SOURCE +$LINENO] ' # Show file name and line number
if [[ -v $DEBUG ]] ; then
    echo "RUNNING IN DEBUG MODE"
    set -u
    trap 'echo "Error: $BASH_SOURCE +$LINENO: command [$BASH_COMMAND] failed with exit code $?" >&2' ERR
fi
# Common defines
CERT=/opt/certification
CERT_HOME=${CERT}/scripts
CERT_INCLUDE_DIR=${CERT_HOME}/cert
CERT_TEST_STATUS_HOME=/tmp/Certification/run
CERT_TEST_OUTPUT=/tmp/Certification/tmp
CERT_LOG_HOME=/tmp/Certification/log
TIMESTAMP_FORMAT="%Y%m%d_%H%M%S"
UTIL_HOME=/usr/local/bin
MISC_HOME=${CERT}/misc
INSMOD_HOME=${MISC_HOME}/kernel
[[ $(hostname) == ubuntu ]] && system_role="DUT" || system_role="AP"

DEV_MODEL=$(tr -d '\0' < /proc/device-tree/model)
REPEATS=3

# BT test
BT_KO=btnxpuart
bt_iface=hci0
bt_test_sleep=5
bt_test_file_src=${MISC_HOME}/test_file.src
BT_RX_MAC="8C:1D:96:F1:87:C1"

# CAN test
can_bitrate=125000
# 0 = off, 1 = animation, 2 = on
can_silent_mode=2

# Cell test - AT modem query
cell_modem="/dev/ttyACM2"
at_modem_speed=9600
at_modem_opts="1:0:cbd:0:3:1c:7f:15:4:5:1:0:11:13:1a:0:12:f:17:16:0:0:0:0:0:0:0:0:0:0:0:0:0:0:0:0"
at_test_modem_timeout=0.5
cell_test_scan_timeout=80
cell_test_sim_timeout=2
cell_rst_gpio_chip=0
cell_rst_gpio=22
sim_detect=0
cell_test_sleep=10
# AT commands
AT_DEFAULT_CMD="AT"
AT_GET_IMEI="AT+CGSN"
AT_GET_ModId="AT+CGMM"
AT_GET_FwId="AT+CGMR"
AT_GET_ICCID="AT+QCCID"
AT_GET_SIMSTAT="AT+QSIMSTAT?"

# Net test
iperf_util=iperf3
net_bandwidth=1M
link_speed=10

# WB test
wb_slot=A
WB_NAME="WB"
# WLAN test
WB_SCENARIO="GW" # [GW|IFM]
wlan_iface=wlan0
WLAN_GW_KO=mwifiex_sdio
wlan_ap="10.42.0.1"
wlan_test_ping_ival="0.7"
wlan_nmcli_HS_con=HotspotCon
wlan_nmcli_WF_con=WifiCon-${wlan_iface}

# DIxOx test
DIO_GET=dioget
DIO_SET=dioset
## DI2O2
di2o2_slot=M
DI2O2_LOOPS_NUM=2
## DI8O8 test
di8o8_slot=C
DI8O8_LOOPS_NUM=8
DI8O8_NAME="DI8O8"

# RS485 test
rs485_sleep=5
rs485_serial_speed=115200
rs485_serial_opts="time 5 ignbrk -brkint -icrnl -imaxbel -opost -onlcr -isig -icanon -iexten -echo -echoe -echok -echoctl -echoke"
rs485_tx=ttyLP4
RS485_NAME="RS485"
rs485_slot=D
Ping="PING"
Pong="pong"
