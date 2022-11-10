/**
 *
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
#include <Screen.h>

#include "configMain.h"

/* Creating the objects to manage the OLED screen on front panel. */
U8G2_SSD1306_128X64_NONAME_F_HW_I2C screen(U8G2_R0, pinSCL, pinSDA);
MainPage mainPage(&screen);

void setup() {
    Serial.begin(baudRate);
    screen.begin();
}

void loop() {
    // TODO: Copy here the Bluetooth connection and read.
    mainPage.show();
}