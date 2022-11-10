 /**
  * @brief This library allows to manage an object "AnalogIn" and/or an object "AnalogOut". You can read, write, manually set or get the value, without worrying about the normalization 
  *  if the resolutions of the two objects are different.
  * If you want to use this class, initially you will have to create the rispective object "AnalogIn" and/or "AnalogOut", for passing them to the constructor. For more information about this class,
  *  read the descriptions of the methods.
  * Copyright (c) 2020 Davide Palladino. 
  * All right reserved.
  * 
  * @author Davide Palladino
  * @contact me@davidepalladino.com
  * @website www.davidepalladino.com
  * @version 2.0.0
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

#ifndef ANALOGCONTROLLER_H
    #define ANALOGCONTROLLER_H

    #include "AnalogIn.h"
    #include "AnalogOut.h"

    class AnalogController {
        public:
            /** 
             * @brief This constructor creates the main object, setting the pointers to the objects where the value will be read and/or write.
             * @param objIn Pointer to object where the value will be read. Set it to "NULL" if will be not used.
             * @param objOut Pointer to object where the value will be written. Set it to "NULL" if will be not used.
             */
            AnalogController(AnalogIn* objIn, AnalogOut* objOut);

            /**
             * @brief This method sets the value. If the AnalogIn object exists, and the resolution is not equal to 0, the max value will be considered from it; else, the max value will be considered from AnalogOut object.
             *  In example, if you set 8-bit as resolution on one of the objects, you can externally set a value between 0 and 255. Else, if the resolution is set to 0, you can set any value at 32 bit.
             * @param value Value to store.
             */
            void setValue(int32_t value);

            /**
             * @brief This method gets the value.
             * @return Value stored.
             */
            int32_t getValue();

            /**
             * @brief This method gets the max value that can be read.
             * @return Max value of AnalogIn object or 0 if the object doesn't exist.
             */
            int32_t getMaxValueIn();

            /**
             * @brief This method gets the max value that can be written.
             * @return Max value of AnalogIOut object or 0 if the object doesn't exist.
             */
            uint16_t getMaxValueOut();

            /**
             * @brief This method gets the resolution that can be read.
             * @return Resolution of AnalogIn object or -1 if the object doesn't exist.
             */
            int8_t getResolutionIn();

            /**
             * @brief This method gets the resolution that can be written.
             * @return Resolution of AnalogIOut object or -1 if the object doesn't exist.
             */
            int8_t getResolutionOut();

            /**
             * @brief This method reads and stores the value from a device, with the AnalogIn object.
             */
            void readValue();

            /**
             * @brief This method writes the value stored to a device, with the AnalogOut object.
             * @return The value that was written, or 0 if AnalogOut object doesn't exist.
             * @warning If the value is less than 0 or greater of the max value of AnalogOut object, will be normalized.
             */
            uint16_t writeValue();

            /**
             * @brief This method writes a percent of the value stored to a device, with the AnalogOut object.
             * @param percent Percent of the value that will be written to the pin.
             * @return The value that was written, considering the percent. 
             * @warning If the value is less than 0 or greater of the max value of AnalogOut object, will be normalized.
             */
            uint16_t writeValue(double percent);

            /**
             * @brief This method activates the blink for certain times and at intervals in milliseconds, with the AnalogOut object. 
             * @param times The number of times.
             * @param timeOut The time in milliseconds for a single interval.
             */
            void blink(uint8_t times, uint32_t timeOut);

        private:
            AnalogIn* objIn;               // Pointer to object where the value will be read. This parameter will be "NULL" if is not set.
            AnalogOut* objOut;             // Pointer to object where the value will be written. This parameter will be "NULL" if is not set.
            int32_t value;                 // Current value read, write or set externally.        
    };
#endif