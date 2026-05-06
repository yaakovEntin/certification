* Get AP running
* run:
```
bash -e <(curl -sL https://raw.githubusercontent.com/yaakovEntin/certification/refs/heads/edge-ai/scripts/main.sh)
```

# Management Cheat Sheet

| **Task**              | **Command**                                             |
| --------------------- | ------------------------------------------------------- |
| **Stop Testing**      | `stop`                                                  |
| **Restart Testing**   | Press `Ctrl+D`                                          |
| **Disable Cell Scan** | `rm /opt/certification/scripts/scan_cell/.autostart`    |
| **Enable Cell Scan**  | `touch /opt/certification/scripts/scan_cell/.autostart` |
| **Set: Network Scan** | `ln -snf bak/cell_scan /opt/certification/cell`         |
| **Set: Alive Check**  | `ln -snf bak/cell_alive /opt/certification/cell`        |

# troubleshooting
## tests log, e.g. ethernet:
```
tail -f /tmp/certification/log/ethernet.log # dynamic
less /tmp/certification/log/ethernet.log # post test
```
