#pragma once

#ifndef ARDUINO_H
        #include <Arduino.h>
#endif

#if defined(ARDUINO_ARCH_ESP32)
        #ifndef ANALOGWRITE_H
                #include <analogWrite.h>
        #endif
        #ifndef ESP32Encoder_H
                #include <ESP32Encoder.h>
        #endif
#endif

#ifndef MATH_H
        #include <math.h>
#endif

#define AIO_MAX_VALUE_BIT8 (int32_t) (pow(2, 8) - 1)
#define AIO_MAX_VALUE_BIT10 (int32_t) (pow(2, 10) - 1)
#define AIO_MIN_VALUE_BIT12 (int32_t) (pow(2, 12) - 1)
#define AIO_MAX_VALUE (int32_t) (pow(2, sizeof(int32_t) * 8) / 2)
#define AIO_MAX_BIT sizeof(int32_t) * 8

typedef enum device : uint8_t {AIO_POTENTIOMETER, AIO_ENCODER} device_t;
typedef enum encoderType : uint8_t {AIO_HALF, AIO_FULL, AIO_SINGLE_EDGE} encoderType_t;