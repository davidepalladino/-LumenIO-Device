 /**
  * @brief This library allows to manage main page for the LED Controller purposes.
  *
  * Copyright (c) 2020 Davide Palladino. 
  * All right reserved.
  *
  * @author Davide Palladino
  * @contact davidepalladino@hotmail.com
  * @website https://davidepalladino.github.io/
  * @version 1.0.0
  * @date 10th November, 2022
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

    #ifndef MATH_H
        #include <math.h>
    #endif

    #ifndef CONFIGSCREEN_H
        #include "../configScreen.h"
    #endif

    class MainPage {
        public:
             /** 
             * @brief This constructor creates the object setting only the pointer to U8G2 object.
             * @param objScreen Pointer to U8G2 object where the operations will be executed.
             * @warning Pointers will have not to be "NULL".
             */
            explicit MainPage(U8G2_SSD1306_128X64_NONAME_F_HW_I2C* objScreen);

            /**
             * @brief This method sets the flag Bluetooth.
             * @param isBluetoothActive Boolean value "true" to indicate if Bluetooth is activated; else "false" value.
             */
            void setIsBluetoothActive(bool isBluetoothActive);

            /**
             * @brief This method gets the flag Bluetooth.
             * @return Boolean value "true" to indicate if Bluetooth is activated; else "false" value.
             */
            bool getIsBluetoothActive();

            /**
             * @brief This method constructs and shows the main page.
             */
            void show(uint8_t red, uint8_t green, uint8_t blue);

        private:
            U8G2_SSD1306_128X64_NONAME_F_HW_I2C* objScreen;         // Pointer to U8G2 object where the operations will be executed. Set it to "NULL" if will be not used.
            bool isBluetoothActive;

            /**
             * @brief This method constructs the notification area, as well as the name of profile and the communications device status.
             */
            void drawNotificationArea();

            /**
             * @brief This method constructs the information area, as well as the values of brightness and the three colors.
             */
            void drawInformationArea(uint8_t red, uint8_t green, uint8_t blue);
    };
#endif