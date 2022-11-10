 /**
  * @brief This is a union class between an object Profile and four objects AnalogController, to manage the values between them.
  * Copyright (c) 2020 Davide Palladino. 
  * All right reserved.
  * 
  * @author Davide Palladino
  * @contact me@davidepalladino.com
  * @website www.davidepalladino.com
  * @version 1.0.0
  * @date 21th November, 2020
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

#ifndef PROFILECONTROLLER_H
    #define PROFILECONTROLLER_H
    #ifndef ARDUINO_H
        #include <Arduino.h>
    #endif

    #ifndef PROFILE_H
        #include <Profile.h>
    #endif

    #ifndef ANALOGIO_H
        #include <AnalogIO.h>
    #endif

    class ProfileController {
        public:            
            /** 
             * @brief This constructor creates the object, setting the pointers to the objects where the colors and the brightness will be read and written.
             * @param objBrightness Pointer to object where will be read the brightness.
             * @param objRed Pointer to object where will be read and written the red color.
             * @param objGreen Pointer to object where will be read and written the green color.
             * @param objBlue Pointer to object where will be read and written the blue color.
             * @warning Pointers will have not to be "NULL".
             */
            ProfileController(AnalogController* objBrightness, AnalogController* objRed, AnalogController* objGreen, AnalogController* objBlue);

            /**
             * @brief This method sets the pointer to Profile object Profile.
             * @param objProfile Pointer to object where will be saved/read the values.
             * @warning Pointer will has not to be "NULL".
             */
            void setProfile(Profile* objProfile);

            /**
             * @brief This method sets the values of brightness and colors on objects AnalogController.
             * @param values An array with the 4 values.
             * @warning Every value will be set only if exists the relative object.
             */
            void setValues(const uint8_t values[4]);

            /**
             * @brief This method gets the pointer to Profile object Profile.
             * @return Pointer to object where will be saved/read the values.
             */
            Profile* getProfile();

            /**
             * @brief This method gets if the brightness is on or not, as well as the value is greater than 0 or not.
             * @return Boolean value "true" if the brightenss is greater than 0; else "false".
             */
            bool getIsOn();

            /**
             * @brief This method gets the error flag.
             * @return Value "true" if there is an error; else "false".
             */
            bool getError();

            /**
             * @brief This method get the name of profile.
             * @return Name of profile. 
             */
            String getNameProfile();

            /**
             * @brief This method gets the values of brightness and colors from objects AnalogController. 
             * @return An array with the 4 values.
             * @warning Use "free" function after the utilization, to prevent overflow of memory heap.
             */
            uint8_t* getValues();

            /**
             * @brief This method gets the read resolutions of the encoders for brightness and colors.
             * @return An array with the 4 values.
             * @warning -1 value implies that the AnalogOut object doesn't exist in AnalogController object. Use "free" function after the utilization, to prevent overflow of memory heap.
             */
            uint8_t* getResolutionsIn();

            /**
             * @brief This method gets the read resolutions of the encoders for brightness and colors.
             * @return An array with the 4 values.
             * @warning -1 value implies that the AnalogOut object doesn't exist in AnalogController object. Use "free" function after the utilization, to prevent overflow of memory heap.
             */
            uint8_t* getResolutionsOut();

            /**
             * @brief This method reads the values from a file.
             * @param nameFile Name of file where the values will be read.
             * @exception This method propagates the exception launched from method of Profile class.
             */
            void readFile() throw(uint8_t);

            /**
             * @brief This method saves the values to a file.
             * @param nameFile Name of file where the values will be saved.
             * @exception This method propagates the exception launched from method of Profile class.
             */
            void writeFile() throw(uint8_t);

            /**
             * @brief This method reads the values from the controller objects.
             * @return Value 1 if there is a change compared to the last read; else value 0.
             */
            uint8_t readDevice();

            /**
             * @brief This method reads the values from the controller objects.
             * @warning Values will be written only if exists firtsly the brightness object.
             */
            void writeDevice();

            /**
             * @brief This method switchs the brightness between 0 and that of profile.
             * @warning The switching there will be only if exists the brightness object.
             */
            void switchOnOff();

        private:
            AnalogController* objBrightness;               // Pointer to object where the brightness will be read and written.
            AnalogController* objRed;                      // Pointer to object where the red color will be read and written.
            AnalogController* objGreen;                    // Pointer to object where the green color will be read and written.
            AnalogController* objBlue;                     // Pointer to object where the blue color will be read and written.
            Profile* objProfile;                           // Pointer to object where the values will be saved/read.
            uint8_t brightnesValue;                        // Value of profile brightness, needed for switching from 0 to this.
            bool isOn;                                     // Boolean value to indicate if the brightness is set to 0 (with "false" value) or to "brightnessValue" (with "true" value).
            bool error;                                    // Boolean value to indicate if there an error (with "true" value) during saved/read operation.

            /**
             * @brief This method sets if the brightness is on or not, as well as the own value is greater than 0 or not.
             * @param isOn Boolean value "true" if the brightenss is greater than 0; else "false".
             */
            void setIsOn(bool isOn);

            /**
             * @brief This method sets the error flag.
             * @param error Value "true" if there is an error; else "false".
             */
            void setError(bool error);

            /**
             * @brief This method sets the value of profile brightness, needed for switching from 0 to this.
             * @param brightnessValue Value of profile brightness.
             */
            void setBrightnesValue(uint8_t brightnessValue);

            /**
             * @brief This method gets the value of profile brightness, needed for switching from 0 to this.
             * @return Value of profile brightness.
             */
            uint8_t getBrightnesValue();
    };
#endif