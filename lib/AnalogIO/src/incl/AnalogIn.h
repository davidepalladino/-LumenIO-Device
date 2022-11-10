/**
  * @brief This library allows to read a value from an analog input like an potentiometer, or from a digital input like an encoder.
  * You can specify the device and the resolution of reading.
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

#ifndef ANALOGIN_H
    #define ANALOGIN_H

    #include "globalData.h"

    class AnalogIn {      
        /* Allow the AnalogController class to access a private methods and attributes. */
        friend class AnalogController;   

        public:
            /** 
             * @brief This constructor creates the object setting only the pin, if the device is a potentiometer.
             * @param pin Analog pin where the value will be read, if the device is a potentiometer.
             * @warning The resolution of reading will be set to 10 bit.
             */
            AnalogIn(uint8_t pin);

            /** 
             * @brief This constructor creates the object setting the pin and the resolution of reading, if the device is a potentiometer.
             * @param pin Analog pin where the value will be read, if the device is a potentiometer.
             * @param resolution Resolution of reading in number of bits. 
             * @warning 12-bit resolution is only for boards DUE, ZERO, MKR and ESP32 family. If you try to set it with a different board, the resolution will be set to 10. 
             *  Same for any value greater than the possible. Number "0" is for encoder's device; if you try to set it, the resolution will be set to 10.
             */
            AnalogIn(uint8_t pin, uint8_t resolution);

            /** 
             * @brief This constructor creates the object setting only the two pins, if the device is an ancoder. Moreover, will be called "pinMode" in "INPUT" mode.
             * @param pin Array with the two digital pins where the value will be read.
             * @warning The resolution of reading will be to 10 bit and the type of encoder will be considered like single edge.
             */
            AnalogIn(const uint8_t pin[2]);

            /** 
             * @brief This constructor creates the object setting the two pins and the resolution of reading, if the device is an ancoder. Moreover, will be called "pinMode" in "INPUT" mode.
             * @param pin Array with the two digital pins where the value will be read.
             * @param resolution Resolution of reading in number of bits. If the resolution is set to 0, the min and max value will be the max possible from your MCU.
             * @warning Type of encoder will be considered like single edge.
             */
            AnalogIn(const uint8_t pin[2], uint8_t resolution);

            /** 
             * @brief This constructor creates the object setting the two pins and the type, if the device is an ancoder. Moreover, will be called "pinMode" in "INPUT" mode.
             * @param pin Array with the two digital pins where the value will be read.
             * @param encoderType Type of encoder if is half quadrature, full quadrature or single edge. Respectively with "AIO_HALF", "AIO_FULL" and "AIO_SINGLE_EDGE".
             * @warning The resolution of reading will be set to 10 bit.
             */
            AnalogIn(const uint8_t pin[2], encoderType_t encoderType);


            /** 
             * @brief This constructor creates the object setting the two pins, the resolution of reading and the type, if the device is an ancoder. Moreover, will be called "pinMode" in "INPUT" mode.
             * @param pin Array with the two digital pins where the value will be read.
             * @param resolution Resolution of reading in number of bits. If the resolution is set to 0, the min and max value will be the max possible from your MCU.
             * @param encoderType Type of encoder if is half quadrature, full quadrature or single edge. Respectively with "AIO_HALF", "AIO_FULL" and "AIO_SINGLE_EDGE".
             */
            AnalogIn(const uint8_t pin[2], uint8_t resolution, encoderType_t encoderType);

            /**
             * @brief This method gets the max value that can be read. 
             * @return Max value that can be read.
             */
            int32_t getMaxValue();

            /**
             * @brief This method reads the value from a device.
             * @return Value between 0 and the max value. If the resolution is set to 0, the min and max value will be the max possible from your MCU.
             */     
            int32_t read();

            /**
             * @brief This method reset the internal value, of encoder object, to a specific value.
             * @param value Value for reset.
             */
            void reset(int32_t value);

        public:
            uint8_t pinA;                       // Pin where the value will be read.
            uint8_t pinB;                       // Pin where the value will be read if the device is an encoder.
            device_t device;                    // Type of device, between "AIO_POTENTIOMETER" and "AIO_ENCODER".
            uint8_t resolution;                 // Resolution in number of bits.
            ESP32Encoder objEncoder;            // Encoder object. Thanks to Kevin Harrington for this powerful class.
            int32_t maxValue;                   // Max value that can be read.
            bool emulatePinA;                   // Flag to indicate if the "pinA" will be emulated or not.
            bool emulatePinB;                   // Flag to indicate if the "pinB" will be emulated or not.

            /**
             * @brief This method sets the pin of the device.
             * @param pinA Analog pin where the value will be read, if the device is a potentiometer; else, digital pin if the device is an encoder.
             */
            void setPinA(uint8_t pinA);

            /**
             * @brief This method sets the pin of the device if is an encoder type.
             * @param pinB Digital pin where the value will be read, if the device is an encoder type.
             */
            void setPinB(uint8_t pinB);

            /**
             * @brief This method sets the type of the device.
             * @param device Value between "AIO_POTENTIOMETER" and "AIO_ENCODER".
             */
            void setDevice(device_t device);

            /**
             * @brief This method sets the resolution in number of bits.
             * @param resolution Value between 0 and the max possible that can be read from you MCU.
             */
            void setResolution(uint8_t resolution);

            /**
             * @brief This method sets the max value that can be read.
             * @param maxValue Max value that can be read.
             */
            void setMaxValue(int32_t maxValue);

            /**
             * @brief This method sets if the "pinA" will be emulated or not in digital.
             * @param status Boolean value "true" if the pin will be emulated; else "false".
             */
            void setEmulatePinA(bool status);

            /**
             * @brief This method sets if the "pinB" will be emulated or not in digital.
             * @param status Boolean value "true" if the pin will be emulated; else "false".
             */
            void setEmulatePinB(bool status);

            /**
             * @brief This method gets the "pinA".
             * @return Analog pin if the device is a potentiometer; else, digital pin if the device is an encoder.
             */         
            uint8_t getPinA();

            /**
             * @brief This method gets the "pinB".
             * @return Digital pin if the device is an encoder.
             */        
            uint8_t getPinB();

            /**
             * @brief This method gets the type of the device.
             * @return Value between "AIO_POTENTIOMETER" and "AIO_ENCODER".
             */    
            device_t getDevice();

            /**
             * @brief This method gets the resolution in number of bits.
             * @return resolution Value between 0 and the max possible that can be read from you MCU.
             */    
            uint8_t getResolution();

            /**
             * @brief This method gets if the "pinA" will be emulated or not in digital.
             * @return Boolean value "true" if the pin will be emulated; else "false".
             */ 
            bool getEmulatePinA();

            /**
             * @brief This method gets if the "pinB" will be emulated or not in digital.
             * @return Boolean value "true" if the pin will be emulated; else "false".
             */ 
            bool getEmulatePinB(); 
    };
#endif