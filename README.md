# pious
Yet another OS project of mine, but this time for an ARM CPU

## Useful documentation for Pi 4
These documents might be helpful for anyone else who wants to do something similar.
[BCM2711 peripherals](https://datasheets.raspberrypi.org/bcm2711/bcm2711-peripherals.pdf)
For the memory map for physical hardware, this will be useful.
[Osdev wiki Pi 4](https://wiki.osdev.org/Raspberry_Pi_4)

## Emulation
Unfortunately, as of right now (21/12/2020), upstream QEMU does not support
the Pi 4 model natively. Since the Pi 3 has different addresses and other
related functions, using the Pi 3 model will almost certainly not work.

There is likely a patch out there, but as I cannot seem to find it, I don't
use it.

As a result, to run pious, you must flash a real SD card and run it on
a real Pi.

## Necessary config.txt
The options I use for config.txt are
```
dtparam=audio=on
dtoverlay=vc4-fkms-v3d
max_framebuffers=2
arm_64bit=1
enable_uart=1
kernel=kernel8.img
dtparam=i2c_arm=on
dtparam=spi=on
core_freq_min=500
disable_overscan=1
enable_gic=1
```
