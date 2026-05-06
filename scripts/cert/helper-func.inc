get_iface_from_devpath() {
    local devpath="$1"
    local iface
    
    if [[ ! -d "$devpath" ]]; then
        echo "ERROR: devpath not found: $devpath" >&2
        return 1
    fi
    
    # Find the network interface in the device path
    # /sys/devices/.../net/ethX -> extract ethX
    iface=$(ls -1 "$devpath/net/" 2>/dev/null | head -1)
    
    if [[ -z "$iface" ]]; then
        echo "ERROR: no network interface found in $devpath" >&2
        return 1
    fi
    
    echo "$iface"
}

do_until_success() {
    local cmd="$1"
    local description="$2"
    local rc=0
    echo "=========================================="
    echo "Running $description"
    echo "=========================================="
    until ${cmd}; do
        echo "FAILED: ${description} (rc=${rc}), retrying..."
        sleep 2
    done
    echo "PASSED: $description"
}
