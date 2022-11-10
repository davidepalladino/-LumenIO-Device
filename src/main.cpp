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
 * @date 10th November, 2022
 *
 */

#include <Arduino.h>
#include <BluetoothSerial.h>

#include "configMain.h"

BluetoothSerial bluetoothSerial;

const byte idDeviceSize = 15;
const byte rgbValuesSize = 3;

char idDevice[idDeviceSize];
byte rgbValues[rgbValuesSize];

void setup() {
    Serial.begin(baudRate);

    uint64_t chipID = ESP.getEfuseMac();

    snprintf(idDevice, idDeviceSize, "%08X", (uint32_t) chipID);
    bluetoothSerial.begin("LumenIO-" + String(idDevice));
}

void loop() {
    if (bluetoothSerial.available()) {
        bluetoothSerial.readBytes(rgbValues, rgbValuesSize);
        Serial.println(rgbValues[0]);
        Serial.println(rgbValues[1]);
        Serial.println(rgbValues[2]);

        analogWrite(pinLedRed, rgbValues[0]);
        analogWrite(pinLedGreen, rgbValues[1]);
        analogWrite(pinLedBlue, rgbValues[2]);
    }
}