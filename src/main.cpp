/**
 * This software allows to manage the led strip (not addressable) via PWM signals. Specifically, get the RGB values via Bluetooth from
 *  an Android App and write them on PWN port.
 *
 * Copyright (c) 2022 Davide Palladino.
 * All right reserved.
 *
 * @author Davide Palladino
 * @contact davidepalladino@hotmail.com
 * @website https://davidepalladino.github.io/
 * @version 2.0.0
 * @date 13th November, 2022
 *
 */

#include <Arduino.h>
#include <BluetoothSerial.h>
#include <EEPROM.h>

#include "config.h"

BluetoothSerial bluetoothSerial;

const byte idDeviceSize = 15;
const byte rgbValuesSize = 3;

char idDevice[idDeviceSize];
byte rgbValuesRead[rgbValuesSize];
byte rgbValuesEEPROM[rgbValuesSize];

unsigned long timeoutSaveEEPROM = 0;

void setup() {
    // For DEBUG
//    Serial.begin(BAUDRATE_SERIAL);

    uint64_t chipID = ESP.getEfuseMac();
    snprintf(idDevice, idDeviceSize, "%08X", (uint32_t) chipID);
    bluetoothSerial.begin("LumenIO-" + String(idDevice));

    EEPROM.begin(SIZE_EEPROM);
    EEPROM.readBytes(ADDRESS_MANUAL_EEPROM, rgbValuesEEPROM, rgbValuesSize);
    EEPROM.end();

    rgbValuesRead[0] = rgbValuesEEPROM[0];
    rgbValuesRead[1] = rgbValuesEEPROM[1];
    rgbValuesRead[2] = rgbValuesEEPROM[2];

    // For DEBUG
//    Serial.println(rgbValuesRead[0]);
//    Serial.println(rgbValuesRead[1]);
//    Serial.println(rgbValuesRead[2]);

    analogWrite(PIN_RED_LED, rgbValuesRead[0]);
    analogWrite(PIN_GREEN_LED, rgbValuesRead[1]);
    analogWrite(PIN_BLUE_LED, rgbValuesRead[2]);
}

void loop() {
    if (bluetoothSerial.available()) {
        bluetoothSerial.readBytes(rgbValuesRead, rgbValuesSize);

    // For DEBUG
//        Serial.println(rgbValuesRead[0]);
//        Serial.println(rgbValuesRead[1]);
//        Serial.println(rgbValuesRead[2]);

        analogWrite(PIN_RED_LED, rgbValuesRead[0]);
        analogWrite(PIN_GREEN_LED, rgbValuesRead[1]);
        analogWrite(PIN_BLUE_LED, rgbValuesRead[2]);

        if (
                ((rgbValuesRead[0] != rgbValuesEEPROM[0]) || (rgbValuesRead[1] != rgbValuesEEPROM[1]) || (rgbValuesRead[2] != rgbValuesEEPROM[2])) &&
                ((rgbValuesRead[0] != 0) || (rgbValuesRead[1] != 0) || (rgbValuesRead[2] != 0))
        ) {
            rgbValuesEEPROM[0] = rgbValuesRead[0];
            rgbValuesEEPROM[1] = rgbValuesRead[1];
            rgbValuesEEPROM[2] = rgbValuesRead[2];

            timeoutSaveEEPROM = millis() + TIME_SAVE_EEPROM;
        }
    }

    if ((timeoutSaveEEPROM < millis()) && (timeoutSaveEEPROM != 0)) {
        timeoutSaveEEPROM = 0;

        EEPROM.begin(SIZE_EEPROM);
        EEPROM.writeBytes(ADDRESS_MANUAL_EEPROM, rgbValuesEEPROM, rgbValuesSize);
        EEPROM.commit();
        EEPROM.end();
    }
}