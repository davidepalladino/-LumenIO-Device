 /**
  * @brief This library allows to manage main page for the LED Controller purposes.
  * Copyright (c) 2020 Davide Palladino. 
  * All right reserved.
  * 
  * @author Davide Palladino
  * @contact me@davidepalladino.com
  * @website www.davidepalladino.com
  * @version 1.0.0
  * @date 18th November, 2020
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

#ifndef MAINPAGE_H
    #define MAINPAGE_H

    #ifndef ARDUINO_H
        #include <Arduino.h>
    #endif

    #ifndef U8G2LIB_H
        #include <U8g2lib.h>
    #endif

    #ifndef PROFILE_H
        #include <Profile.h>
    #endif  

    #ifndef MATH_H
        #include <math.h>
    #endif

    #ifndef CONFIGSCREEN_H
        #include "../configScreen.h"
    #endif

    /* Structure to save the status of communication devices. */
    typedef struct {
        bool isBluetoothActive;
        bool isWifiActive;
    } connectionsFlags_t;

    /* Structure to save the status of banner. */
    typedef struct {
        bool isActive;
        unsigned long endTimeout;
        String text;
    } banner_t;

    class MainPage {
        public:
             /** 
             * @brief This constructor creates the object setting only the pointer to U8G2 object.
             * @param objScreen Pointer to U8G2 object where the operations will be executed.
             * @param objProfile Pointer to ProfileController object where will be read the values.
             * @warning Pointers will have not to be "NULL".
             */
            MainPage(U8G2_SSD1306_128X64_NONAME_F_HW_I2C* objScreen, ProfileController* objProfile);

            /**
             * @brief This method sets the flag Bluetooth.
             * @param isBluetoothActive Boolean value "true" to indicate if Bluetooth is activated; else "false" value.
             */
            void setIsBluetoothActive(bool isBluetoothActive);

            /**
             * @brief This method sets the flag WiFi.
             * @param isWifiActive Boolean value "true" to indicate if WiFi is activated; else "false" value.
             */
            void setIsWifiActive(bool isWifiActive);

            /**
             * @brief This method gets the flag Bluetooth.
             * @return Boolean value "true" to indicate if Bluetooth is activated; else "false" value.
             */
            bool getIsBluetoothActive();

            /**
             * @brief This method gets the flag WiFi.
             * @return Boolean value "true" to indicate if WiFi is activated; else "false" value.
             */
            bool getIsWifiActive();

            /**
             * @brief This method actives the banner, changing the values of the relative structure.
             * @param text Message to show.
             */
            void activateBanner(String text);

            /**
             * @brief This method deactives the banner, changing the values of the relative structure.
             */
            void deactivateBanner();

            /**
             * @brief This method constructs and shows the main page.
             */
            void show();

        private:
            U8G2_SSD1306_128X64_NONAME_F_HW_I2C* objScreen;         // Pointer to U8G2 object where the operations will be executed. Set it to "NULL" if will be not used.
            ProfileController* objProfile;                          // Pointer to ProfileController object where will be considerated the informations.
            connectionsFlags_t connectionsFlags;                      // Structure to indicate the status of communication devices.
            banner_t banner;                                        // Structure to manage the banner.

            /**
             * @brief This method sets the flag of activation of banner.
             * @param isActive Boolean value "true" to indicate if the banner is activated; else "false" value.
             */
            void setIsBannerActive(bool isActive);
            
            /**
             * @brief This method sets the time to end the showing of banner.
             * @param endTimeout Value in milliseconds.
             */
            void setBannerEndTimeout(unsigned long endTimeout);

            /**
             * @brief This method sets the text to show on the banner.
             * @param text String to show.
             */
            void setBannerText(String text);

            /**
             * @brief This method gets the flag of activation of banner.
             * @return Boolean value "true" to indicate if the banner is activated; else "false" value.
             */
            bool getIsBannerActive();
            
            /**
             * @brief This method gets the time to end the showing of banner.
             * @return Value in milliseconds.
             */
            unsigned long getBannerEndTimeout();

            /**
             * @brief This method gets the text to show on the banner.
             * @return String to show.
             */
            String getBannerText();
            
            /**
             * @brief This method constructs the notification area, as well as the name of profile and the communications device status.
             */
            void drawNotificationArea();

            /**
             * @brief This method constructs the information area, as well as the values of brightness and the three colors.
             */
            void drawInformationArea();

            /**
             * @brief This method constructs the banner with the text set.
             */
            void drawBanner(); 
    };
#endif