 /**
  * This software allows to manage the hardware of "LED Controller". Specifically, you can manage the brigthness and the three colrs (red, green and blue color). 
  * If you want you can save or read the configuration from SD card; for this, you have three slot.
  * Copyright (c) 2020 Davide Palladino. 
  * All right reserved.
  * 
  * @author Davide Palladino
  * @contact me@davidepalladino.com
  * @website www.davidepalladino.com
  * @version 2.0.1
  * @date 24th November, 2020
  * 
  */

#include <Arduino.h>
#include <EEPROM.h>
//#include <WiFi.h>

#include <AnalogIO.h>
#include <Button.h>
#include <Profile.h>
#include <Screen.h>
#include <AddressableStrip.h>

#include "configMain.h"

/* Creating the objects for managing the encoders. */
AnalogIn encoderBrightness(pinEncoderBrightness, resolutionIn, AIO_SINGLE_EDGE);
AnalogIn encoderRed(pinEncoderRed, resolutionIn, AIO_SINGLE_EDGE);
AnalogIn encoderGreen(pinEncoderGreen, resolutionIn, AIO_SINGLE_EDGE);
AnalogIn encoderBlue(pinEncoderBlue, resolutionIn, AIO_SINGLE_EDGE);

/* Creating the objects for managing the LED strip. */
AnalogOut stripLedRed(pinStripLedRed, resolutionOut);
AnalogOut stripLedGreen(pinStripLedGreen, resolutionOut);
AnalogOut stripLedBlue(pinStripLedBlue, resolutionOut);

/* Creating the objects controller to manage the encoder and the respective color on LED strip. */
AnalogController brightness(&encoderBrightness, NULL);
AnalogController red(&encoderRed, &stripLedRed);
AnalogController green(&encoderGreen, &stripLedGreen);
AnalogController blue(&encoderBlue, &stripLedBlue);

/* Creating the profiles and the object controller. */
Profile profileManual(nameProfileManual, directoryProfiles, fileNameProfileManual);
Profile profile1(nameProfile1, directoryProfiles, fileNameProfile1);
Profile profile2(nameProfile2, directoryProfiles, fileNameProfile2);
Profile profile3(nameProfile3, directoryProfiles, fileNameProfile3);
ProfileController profileController(&brightness, &red, &green, &blue);

/* Creating the objects for the knobs on front panel. */
Button buttonOnOff(pinButtonProfileOnOff, B_PULLUP);
Button buttonProfile1(pinButtonProfile1, B_PULLUP, timeLongPress);
Button buttonProfile2(pinButtonProfile2, B_PULLUP, timeLongPress);
Button buttonProfile3(pinButtonProfile3, B_PULLUP, timeLongPress);

/* Creating the objects to manage the OLED screen on front panel. */
U8G2_SSD1306_128X64_NONAME_F_HW_I2C screen(U8G2_R0, pinSCL, pinSDA);
MainPage mainPage(&screen, &profileController);

/* Creating the object to manage the LED strip addressable on top. */
AddressableStrip indicatorLed(pinData, nLed, &profileController);

/* Creating a variabile that will contain the number of profile selected, for reading/writing the values. */
int8_t profileSelected = -1;          // -1 stands for not set.

/* Creating the variable to manage the manual configuration. */
unsigned long endTimeoutManual;       // This will contain the time where the manual configuration will be saved on "fileNameManual".

/* Creating a variable to contain the last status of button. */
int8_t resultButton;

void setup() {
  Serial.begin(baudRate);
  EEPROM.begin(sizeEEPROM);
  screen.begin();
  indicatorLed.begin();

  /* START: WiFi connection.
  WiFi.mode(WIFI_STA);
  WiFi.begin("Palladino", "pulcinopatatino8");
  WiFi.setHostname("LED Controller");
  Serial.print("Connecting to WiFi...");
  while (WiFi.status() != WL_CONNECTED) {
    Serial.print(".");
    delay(1000);
  }
  Serial.print("\nConnected. My IP address is: ");
  Serial.println(WiFi.localIP());
  Serial.print("My MAC address is: ");
  Serial.println(WiFi.macAddress());
  Serial.print("My hostname is: ");
  Serial.println(WiFi.getHostname());
  END: WiFi connection. */

  /* Setting the CS pin. */
  Profile::setPinCS(pinCS);

  /* Getting the last profile read/written from EEPROM for the next execution it. */
  switch (EEPROM.read(addressEEPROMNumProfile)) {
    case 0:
      profileController.setProfile(&profileManual);
      break;
    case 1:
      profileController.setProfile(&profile1);
      break;
    case 2:
      profileController.setProfile(&profile2);
      break;
    case 3:
      profileController.setProfile(&profile3);
      break;
  }

  /* Execution the operation of reading. In case of error, will be launched an exception with a notification on the screen and indicator LED. */
  try {
    profileController.readFile();
    profileController.writeDevice();
  } catch (uint8_t error) {
    mainPage.activateBanner(labelBannerErrorSD);
  }
}

void loop() {
  indicatorLed.show(); 
  mainPage.show();

  /* Checking if there is a switch of brightness. */
  if (buttonOnOff.checkPress() != 0) {
    profileController.switchOnOff();
    profileController.writeDevice();
  }

  /* Reading from the device through the "profileController". If there is a change, 
   * will start the timeout by which is possible to an another change, without saves it. 
   * In this last case the timeout will be reset. 
   */  
  if (profileController.readDevice()) {
    profileController.writeDevice();
    mainPage.deactivateBanner();

    endTimeoutManual = millis() + timeoutSaveManual;
  }

  /* Checking if the timeout is ended and setting the manual profile. */
  if ((millis() > endTimeoutManual) && (endTimeoutManual > 0)) {
    endTimeoutManual = 0;
    
    try {
      profileController.setProfile(&profileManual);
      profileController.writeFile();

      mainPage.deactivateBanner();

      profileSelected = 0;
    } catch (uint8_t error) {
      mainPage.activateBanner(labelBannerErrorSD);
    }
  }

  /* Reading the status of buttons through the button, setting "profileController" and resetting "isTimeStarted". */
  resultButton = 0;
  if ((resultButton = buttonProfile1.checkPress()) != 0) {
    profileController.setProfile(&profile1);
    profileSelected = 1;
  } else if ((resultButton = buttonProfile2.checkPress()) != 0) {
    profileController.setProfile(&profile2);
    profileSelected = 2;
  } else if ((resultButton = buttonProfile3.checkPress()) != 0) {
    profileController.setProfile(&profile3);
    profileSelected = 3;
  }

  /* Checking the resultButton and executing the right operation. In case of error, will be launched an exception. */
  try {
    if (resultButton != 0) {
      endTimeoutManual = 0;

      if (resultButton == -1) {
        profileController.writeFile();
        mainPage.activateBanner(labelBannerProfileSaved);
      } else if (resultButton == 1) {
        profileController.readFile();
        profileController.writeDevice();

        mainPage.deactivateBanner();
      }
    }
  } catch (uint8_t error) {
      mainPage.activateBanner(labelBannerErrorSD);
  }

  /* Storing the number of last profile on the EEPROM, applying it and resetting "profileSelected". */
  if (profileSelected != -1) {
      if ((uint8_t) EEPROM.read(addressEEPROMNumProfile) != profileSelected) {
        EEPROM.write(addressEEPROMNumProfile, (uint8_t) profileSelected);
        EEPROM.commit();
      }

      profileSelected = -1;
  }
}