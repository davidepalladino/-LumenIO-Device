#pragma once
#define DEBUG 0           // Be careful! Make the MCU slower. Use it only when is necessary.

// LED strip
const uint8_t PIN_RED_LED =                         16;
const uint8_t PIN_GREEN_LED =                       15;
const uint8_t PIN_BLUE_LED =                        17;

// Serial Monitor
const uint32_t BAUDRATE_SERIAL =                    115200;

// EEPROM
const uint8_t SIZE_EEPROM =                         3;
const uint8_t ADDRESS_RGB_VALUES_EEPROM =           0;          // Size: 3
const uint16_t TIME_SAVE_EEPROM =                   3000;