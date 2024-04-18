# LumenIO-Device
This firmware provides to get and _realize_ the RAW values (RGB and intensity) received from the [Android application](https://github.com/davidepalladino/LumenIO-AndroidApp).

## Components used
For this project I'm using these components:
- MH-ET LIVE D1 mini ESP32;
- LED strip RGB 5050 SMD not addressable at 12V.

For other related components, read the [dedicated article](https://davidepalladino.github.io/2024/04/19/LumenIO-v1-0-0/).

### Pinout
| Pin | What                |
|-----|---------------------|
| 16  | PWM for RED color   |
| 15  | PWM for GREEN color |
| 17  | PWM for BLUE color  |

## Installation
### Compile and flash
After cloning this repository, open it with your IDE that has PlatformIO. 
If you didn't install it, follow the [official documentation](https://docs.platformio.org/en/latest/integration/ide/pioide.html) both installation and build.

### A little impatient
Otherwise, you can **download** the firmware [from here](https://davidepalladino.github.io/2024/04/19/LumenIO-v1-0-0/download/lumenio-firmware.bin)!
To flash the firmware, follow this section of [official documentation](https://docs.espressif.com/projects/esptool/en/latest/esp32/esptool/flashing-firmware.html#id1),
or another documentation if you want to use another MCU.

## Related posts
* [LED Controller v1.0.0](https://davidepalladino.github.io/2020/09/25/LED-Controller-v1-0-0/)
* [LumenIO v1.0.0](https://davidepalladino.github.io/2024/04/19/LumenIO-v1-0-0/)