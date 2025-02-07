# LumenIO-Device
This firmware is designed to receive and process RAW values (RGB and intensity) from the [LumenIO Android application](https://github.com/davidepalladino/LumenIO-AndroidApp).

## Components Used
For this project, the following components are utilized:
- **Microcontroller** MH-ET LIVE D1 mini ESP32;
- **LED Strip** RGB 5050 SMD non-addressable, 12V.

For additional related components, please refer to the [dedicated article](https://davidepalladino.github.io/2024/04/19/LumenIO-v1-0-0/).

### Pinout Configuration
The components are connected to the MH-ET LIVE D1 mini ESP32 as follows:

| Pin | Function        |
|-----|-----------------|
| 16  | PWM for RED     |
| 15  | PWM for GREEN   |
| 17  | PWM for BLUE    |

## Installation
### Compile and Flash
1. **Clone the Repository**:
   
   ```bash
   git clone https://github.com/davidepalladino/LumenIO-Device.git
   ```
2. **Install PlatformIO**:
   
   Follow the instructions on the [PlatformIO website](https://platformio.org/install) to install the PlatformIO IDE.
3. **Open the Project**:
   
   Launch PlatformIO and open the cloned project directory.
4. **Configure the Environment**:
   
   Ensure that the `platformio.ini` file is set up correctly for the MH-ET LIVE D1 mini ESP32 board.
5. **Upload the Firmware**:
   
   Connect your MH-ET LIVE D1 mini ESP32 board to your computer and upload the firmware using PlatformIO.

### Precompiled Firmware
If you prefer not to compile the firmware yourself, you can download the precompiled version [from here](https://davidepalladino.github.io/2024/04/19/LumenIO-v1-0-0/download/lumenio-firmware.bin). To flash the firmware onto your device, follow the [official documentation](https://docs.espressif.com/projects/esptool/en/latest/esp32/esptool/flashing-firmware.html#id1) or other relevant guides for your specific microcontroller unit (MCU).

## Related Resources
- **[LED Controller v1.0.0](https://davidepalladino.github.io/)**;
- **[LumenIO v1.0.0](https://davidepalladino.github.io/)**.

## License
This project is licensed under the MIT License.

## Acknowledgments
Special thanks to the contributors and the open-source community for their support and resources.

---

*Note: This project is part of the LumenIO system, which includes both firmware and an Android application for comprehensive device management.*
