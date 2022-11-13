// LED strip
const uint8_t PIN_RED_LED =                         16;
const uint8_t PIN_GREEN_LED =                       15;
const uint8_t PIN_BLUE_LED =                        17;

// Serial Monitor
const uint32_t BAUDRATE_SERIAL =                    115200;

// EEPROM
const uint8_t SIZE_EEPROM =                         13;
const uint8_t ADDRESS_SCENE_SELECTED_EEPROM =       0;          // Size: 1
const uint8_t ADDRESS_MANUAL_EEPROM =               1;          // Size: 3
const uint8_t ADDRESS_SCENE_ONE_EEPROM =            4;          // Size: 3
const uint8_t ADDRESS_SCENE_TWO_EEPROM =            7;          // Size: 3
const uint8_t ADDRESS_SCENE_THREE_EEPROM =          10;         // Size: 3
const uint16_t TIME_SAVE_EEPROM =                   5000;