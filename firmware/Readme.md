# Resources

* https://honzafiala.github.io/webscope/
* `chrome://device-log/` for device logs

# AUthorisations

```shell
kelu@hp:~/projets/0xA5EDED$ more /etc/udev/rules.d/99-tinyusb.rules
# Copy this file to the location of your distribution's udev rules, for example on Ubuntu:
#   sudo cp 99-tinyusb.rules /etc/udev/rules.d/
# Then reload udev configuration by executing:
#   sudo udevadm control --reload-rules
#   sudo udevadm trigger

# Check SUBSYSTEM
SUBSYSTEMS=="hidraw", KERNEL=="hidraw*", MODE="0666", GROUP="dialout"

# Rule applies to all TinyUSB example
ATTRS{idVendor}=="cafe", MODE="0666", GROUP="dialout"

# Rule to blacklist TinyUSB example from being manipulated by ModemManager.
SUBSYSTEMS=="usb", ATTRS{idVendor}=="cafe", ENV{ID_MM_DEVICE_IGNORE}="1"

kelu@hp:~/projets/0xA5EDED$ 
```