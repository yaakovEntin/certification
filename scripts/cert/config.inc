#DEBUG=1
export PS4='[$BASH_SOURCE +$LINENO] ' # Show file name and line number
if [[ -v $DEBUG ]] ; then
    echo "RUNNING IN DEBUG MODE"
    VERBOSE=1
    set -u
    trap 'echo "Error: $BASH_SOURCE +$LINENO: command [$BASH_COMMAND] failed with exit code $?" >&2' ERR
fi
# Common defines
CERT=/opt/certification
CERT_HOME=${CERT}/scripts
CERT_INCLUDE_DIR=${CERT_HOME}/cert
CERT_TMP=/tmp/certification
CERT_TEST_STATUS_HOME=${CERT_TMP}/run
CERT_TEST_OUTPUT=${CERT_TMP}/tmp
CERT_LOG_HOME=${CERT_TMP}/log
UTIL_HOME=/usr/local/bin
MISC_HOME=${CERT}/misc
[[ $(hostname) == ubuntu ]] && system_role="DUT" || system_role="AP"

REPEATS=3

# BT test
BT_KO=btnxpuart
bt_iface=hci0
bt_test_sleep=5
bt_test_file_src=${MISC_HOME}/test_file.src
BT_RX_MAC="A0:D3:65:BD:E1:23"

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
AT_GET_ICCID="AT+QCCID"
AT_GET_SIMSTAT="AT+QSIMSTAT?"

# WLAN test
wlan_iface=wlan0
wlan_ap="10.42.0.1"
wlan_test_ping_ival="0.7"
wlan_nmcli_HS_con=HotspotCon
wlan_nmcli_WF_con=WifiCon-${wlan_iface}
