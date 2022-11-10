/**
  * @brief This library allows to write a value on digital output, exactly on PWM pin. 
  * You can specify the resolution of writing.
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

#ifndef ANALOGOUT_H
    #define ANALOGOUT_H
    
    #include "globalData.h"

    class AnalogOut {
        /* Allow the AnalogController class to access a private methods and attributes. */
        friend class AnalogController;

        public:
            /** 
             * @brief This constructor creates the object setting only the pin of writing. 
             * @param pin Digital pin where the value will be written.
             * @warning The resolution of writing will be set to 8 bit.
             */
            AnalogOut(uint8_t pin);

            /** 
             * @briefThis constructor creates the object setting the pin and the resolution of writing. 
             * @param pin Digital pin where the value will be written.
             * @param resolution Resolution of reading in number of bits. 
             * @warning 10-bit and 12 bit resolutions is only for boards DUE, ZERO or MKR family. If you try to set it with a different board, the resolution will be set to 8.  
             *  Same for any value greater than the possible, or if the value is equal to 0.
             */
            AnalogOut(uint8_t pin, uint8_t resolution);

            /**
             * @brief This method gets the max value that can be written.
             * @return Max value that can be written.
             */
            uint16_t getMaxValue();

            /**
             * @brief This method writes the value to the pin.
             * @param value Value to write, between 0 and the max value.
             * @return Value written.
             */     
            uint16_t write(uint16_t value);

        private:
            uint8_t pin;                        // Pin where the value will be written. 
            uint8_t resolution;                 // Resolution in number of bits.
            uint16_t maxValue;                  // Max value that can be written.

            /**
             * @brief This method sets the pin where the value will be written.
             * @param pin Digital pin where the value will be written.
             */
            void setPin(uint8_t pin);

            /**
             * @brief This method sets the resolution in number of bits.
             * @param resolution Value between 0 and 12.
             */
            void setResolution(uint8_t resolution);

            /**
             * @brief This method sets the max value that can be written.
             * @param maxValue Max value that can be written.
             */
            void setMaxValue(uint16_t maxValue);

            /**
             * @brief This method gets the pin where the value will be written. 
             * @return Digital pin where the value will be written. 
             */         
            uint8_t getPin();

            /**
             * @brief This method gets the resolution in number of bits.
             * @return resolution Value between 0 and 12.
             */    
            uint8_t getResolution();
    };
#endif