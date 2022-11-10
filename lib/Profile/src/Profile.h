 /**
  * @brief This library allows to manage the profile stored on SD card, for purposes of LED Controller. Every profile has a name, filename and the own directory.
  * The pin CS set in this class is shared fot all objects.
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

#include "incl/ProfileController.h"

#ifndef PROFILE_H
    #define PROFILE_H
    #ifndef ARDUINO_H
        #include <Arduino.h>
    #endif

    #ifndef SD_H
        #include <SD.h>
    #endif

    class Profile {
        public:            
            /** 
             * @brief This constructor creates the object, setting the name of profile, filename and the own directory.
             * @param nameProfile Name of profile.
             * @param directory Directory where is located the profile.
             * @param fileName Filename of the profile, with extension.
             */
            Profile(String nameProfile, String directory, String fileName);

            /**
             * @brief This method sets the name of profile.
             * @param nameProfile Name of profile.
             */
            void setNameProfile(String nameProfile);

            /**
             * @brief This method sets the directory where is located the profile.
             * @param directory Directory where is located the profile.
             */
            void setDirectory(String directory);

            /**
             * @brief This method sets the filename where the values will be saved/read.
             * @param fileName Filename where the values will be saved/read, with extension.
             */
            void setFileName(String fileName);

            /**
             * @brief This method sets the CS pin for all objects of this class.
             * @param pin Pin where is connected the SD card reader.
             */
            static void setPinCS(uint8_t pin);

             /**
             * @brief This method gets the name of profile.
             * @return Name of profile.
             */
            String getNameProfile();

            /**
             * @brief This method gets the directory where is located the profile.
             * @return Directory where is located the profile.
             */
            String getDirectory();

            /**
             * @brief This method gets the fileName where the values will be saved/read.
             * @return Filename where the values will be saved/read, with extension.
             */
            String getFileName();
        
            /**
             * @brief This method gets the CS pin for all objects of this class.
             * @return Pin where is connected the SD card reader.
             */
            static uint8_t getPinCS();

            /**
             * @brief This method reads the values from the file.
             * @return An array with the 4 values.
             * @exception Value 0 if there is an error during the connection to SD card reader; 1 if there is an error during the opening of file. 
             * @warning Use "free" function after the utilization, to prevent overflow of memory heap.
             */
            uint8_t* readFile() throw(uint8_t);

            /**
             * @brief This method saves the values to a file.
             * @param values An array with the 4 values.
             * @exception Value 0 if there is an error during the connection to SD card reader; 1 if there is an error during the opening of file. 
             */
            void writeFile(const uint8_t values[4]) throw(uint8_t);

        private:
            String nameProfile;                            // Name of profile.
            String fileName;                               // Filename where to save/read the values, with extension.
            String directory;                              // Directory where is located the profile.
            static uint8_t pinCS;                          // Pin where is connected the SD card reader.
    };
#endif