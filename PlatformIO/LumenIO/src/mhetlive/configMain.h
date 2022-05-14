// Encoders
const uint8_t pinEncoderBrightness[2] =     {10, 13};
const uint8_t pinEncoderRed[2] =            {26, 36};
const uint8_t pinEncoderGreen[2] =          {39, 35};
const uint8_t pinEncoderBlue[2] =           {33, 34};
const uint8_t resolutionIn =                8;
const uint8_t resolutionOut =               8;

// LED strip
const uint8_t pinStripLedRed =              16;
const uint8_t pinStripLedGreen =            15;
const uint8_t pinStripLedBlue =             17;

// Buttons
const uint8_t pinButtonProfile1 =           4;
const uint8_t pinButtonProfile2 =           32;
const uint8_t pinButtonProfile3 =           27;
const uint8_t pinButtonProfileOnOff =       14;
const uint16_t timeLongPress =              3000;

// SD card reader
const uint8_t pinCS =                       5;
const String directoryProfiles =            "/";
const String fileNameProfileManual =        "manual.dat"; 
const String fileNameProfile1 =             "profile1.dat";
const String fileNameProfile2 =             "profile2.dat";
const String fileNameProfile3 =             "profile3.dat";
const String nameProfileManual =            "Manual";
const String nameProfile1 =                 "Profile 1";
const String nameProfile2 =                 "Profile 2";
const String nameProfile3 =                 "Profile 3";
const uint16_t timeoutSaveManual =          5000;

// LED Indicator
const uint8_t nLed =                        4;
const uint8_t pinData =                     25;

// OLED screen
const uint8_t pinSCL =                      22;
const uint8_t pinSDA =                      21;
const String labelBannerErrorSD =           "ERROR: Can't read profile. Check the SD reader.";
const String labelBannerProfileSaved =      "NOTICE: Profile saved.";

// EEPROM
const uint8_t sizeEEPROM =                  1;
const uint8_t addressEEPROMNumProfile =     0;

// Serial Monitor
const uint32_t baudRate =                   115200;