 /**
  * @brief This library allows to manage an addressable led strip SK6812. You can specify the number of leds and the colors.
  * Copyright (c) 2020 Davide Palladino. 
  * All right reserved.
  * 
  * @author Davide Palladino
  * @contact me@davidepalladino.com
  * @website www.davidepalladino.com
  * @version 1.0.0
  * @date 17th November, 2020
  * 
  * This library is free software; you can redistribute it and/or
  *  modify it under the terms of the GNU General Public
  *  License as published by the Free Software Foundation; either
  *  version 3.0 of the License, or (at your option) any later version
  * 
  * This library is distributed in the hope that it will be useful,
  *  but WITHOUT ANY WARRANTY; without even the implied warranty of
  *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the 
  *  GNU Lesser General Public License for more details.
  * 
  */

#ifndef ADDRESSABLESTRIP_H
    #define ADDRESSABLESTRIP_H

    #ifndef ARDUINO_H
        #include <Arduino.h>
    #endif

    #ifndef NEOPIXELBUS_H
        #include <NeoPixelBus.h>
    #endif

    #ifndef PROFILE_H
        #include <Profile.h>
    #endif

    #ifndef CONFIGADDRESSABLESTRIP_H
        #include "../configAddressableStrip.h"
    #endif

    class AddressableStrip {
        public:
            /** 
             * @brief This constructor creates the object setting the pin data, the number of leds and the profile to check the status.
             * @param pinData Digital pin where is connected the addressable led strip.
             * @param nLed Number of leds.
             * @param objProfile Pointer to "Profile" object to check the status.
             */
            AddressableStrip(uint8_t pinData, uint8_t nLeds, ProfileController* objProfile);

            /**
             * @brief This method tells to MCU to communicate with the addressable led strip.
             */
            void begin();

            /**
             * @brief This method update the addressable led strip with the colors set.
             */
            void show();
            
        private:
            NeoPixelBus<NeoGrbwFeature, Neo800KbpsMethod>* objLed;           // Pointer to "NeoPixelBus" object.
            RgbwColor* objColorsPowerOn;                                     // Pointer to "RgbwColor" object that indicates the power on status.
            RgbwColor* objColorsStandby;                                     // Pointer to "RgbwColor" object that indicates the standby status.
            RgbwColor* objColorsError;                                       // Pointer to "RgbwColor" object that indicates the error status.
            ProfileController* objProfile;                                   // Pointer to "ProfileController" object to check the status.

            /**
             * @brief This method populate all leds with the same color.
             * @param objColors Pointer to "RgbwColor" object where to get the colors values.
             */
            void populateAllLed(RgbwColor* objColors);
    };
#endif