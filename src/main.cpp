/**
 * This software allows to manage the led strip (not addressable) via PWM signals. Specifically, get the RGB values via Bluetooth from
 *  an Android App and write them on PWN port.
 *
 * Copyright (c) 2024 Davide Palladino.
 * All right reserved.
 *
 * @author Davide Palladino
 * @contact davidepalladino@hotmail.com
 * @website https://davidepalladino.github.io/
 * @version 2.1.0
 * @date 12th January 2025
 *
 */

#include <Arduino.h>
#include <BluetoothSerial.h>
#include <EEPROM.h>

#include "soc/soc.h"
#include "soc/rtc_cntl_reg.h"

#include "config.h"

BluetoothSerial bluetoothSerial;

const byte idDeviceSize = 15;
const byte rgbValuesSize = 3;

char idDevice[idDeviceSize];
byte rgbValuesRead[rgbValuesSize];
byte rgbValuesEEPROM[rgbValuesSize];

unsigned long timeoutSaveEEPROM = 0;

void setup() {
    // Disabling brownout detector
    WRITE_PERI_REG(RTC_CNTL_BROWN_OUT_REG, 0);

    #if DEBUG
    Serial.begin(BAUDRATE_SERIAL);
    #endif

    uint64_t chipID = ESP.getEfuseMac();
    snprintf(idDevice, idDeviceSize, "%08X", (uint32_t) chipID);
    bluetoothSerial.begin("LumenIO-" + String(idDevice));

    EEPROM.begin(SIZE_EEPROM);
    EEPROM.readBytes(ADDRESS_MANUAL_EEPROM, rgbValuesEEPROM, rgbValuesSize);
    EEPROM.end();

    rgbValuesRead[0] = rgbValuesEEPROM[0];
    rgbValuesRead[1] = rgbValuesEEPROM[1];
    rgbValuesRead[2] = rgbValuesEEPROM[2];

    #if DEBUG
    Serial.println("\033[1;36m----- [PACKETS] -----\033[0m");
    Serial.printf("\033[1;91m%u\033[0m\n", rgbValuesRead[0]);
    Serial.printf("\033[1;92m%u\033[0m\n", rgbValuesRead[1]);
    Serial.printf("\033[1;94m%u\033[0m\n", rgbValuesRead[2]);
    Serial.println("\033[1;36m---------------------\033[0m");
    #endif

    analogWrite(PIN_RED_LED, rgbValuesRead[0]);
    analogWrite(PIN_GREEN_LED, rgbValuesRead[1]);
    analogWrite(PIN_BLUE_LED, rgbValuesRead[2]);
}

void loop() {
    if (bluetoothSerial.available()) {
        bluetoothSerial.readBytes(rgbValuesRead, rgbValuesSize);

        #ifdef DEBUG
        Serial.println("\033[1;36m----- [PACKETS] -----\033[0m");
        Serial.printf("\033[1;91m%u\033[0m\n", rgbValuesRead[0]);
        Serial.printf("\033[1;92m%u\033[0m\n", rgbValuesRead[1]);
        Serial.printf("\033[1;94m%u\033[0m\n", rgbValuesRead[2]);
        Serial.println("\033[1;36m---------------------\033[0m");
        #endif

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