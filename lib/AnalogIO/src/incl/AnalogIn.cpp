#include "AnalogIn.h"

AnalogIn::AnalogIn(uint8_t pin) : AnalogIn (pin, 10) {}

AnalogIn::AnalogIn(uint8_t pin, uint8_t resolution) {
    setPinA(pin);
    setDevice(AIO_POTENTIOMETER);
    setResolution(resolution);
    setMaxValue((int32_t) (pow(2, getResolution()) - 1));
}

AnalogIn::AnalogIn(const uint8_t pin[2]) : AnalogIn(pin, 10, AIO_SINGLE_EDGE) {}

AnalogIn::AnalogIn(const uint8_t pin[2], encoderType_t encoderType) : AnalogIn(pin, 10, encoderType) {}

AnalogIn::AnalogIn(const uint8_t pin[2], uint8_t resolution) : AnalogIn(pin, resolution, AIO_SINGLE_EDGE) {}

AnalogIn::AnalogIn(const uint8_t pin[2], uint8_t resolution, encoderType_t encoderType) {
    setPinA(pin[0]);
    setPinB(pin[1]);

    setDevice(AIO_ENCODER);

    switch (encoderType) {
        case AIO_HALF:
            objEncoder.attachHalfQuad(getPinA(), getPinB());
        case AIO_FULL:
            objEncoder.attachFullQuad(getPinA(), getPinB());
        case AIO_SINGLE_EDGE:
            objEncoder.attachSingleEdge(getPinA(), getPinB());
    }
    reset(0);
    
    setResolution(resolution);

    if (getResolution() == 0) {
        setMaxValue(AIO_MAX_VALUE);
    } else {
        setMaxValue((uint32_t) (pow(2, getResolution()) - 1));
    }

    setEmulatePinA((bool) !digitalRead(getPinA()));
    setEmulatePinB((bool) !digitalRead(getPinB()));
}

int32_t AnalogIn::getMaxValue() { return this->maxValue; }

int32_t AnalogIn::read() {
    /* Checking if the device is an potentiometer or an encoder. In both cases, will be return the value; else the number "0". */
    if (getDevice() == AIO_POTENTIOMETER) {
        if (getMaxValue() < AIO_MAX_VALUE_BIT10) {
            return map(analogRead(getPinA()), 0, AIO_MAX_VALUE_BIT10, 0, getMaxValue());
        } else {
            return analogRead(getPinA());
        }
    } else if (getDevice() == AIO_ENCODER) {
        if (objEncoder.getCount() > getMaxValue()) {
            objEncoder.setCount(getMaxValue());
        } else if (objEncoder.getCount() < 0) {
            if (getResolution() != 0) {
                objEncoder.setCount(0);
            } else if (objEncoder.getCount() < (-getMaxValue())) {
                objEncoder.setCount(-getMaxValue());
            } 
        }
        
        return objEncoder.getCount();
    } else {
        return 0;
    }
}

void AnalogIn::reset(int32_t value) { objEncoder.setCount(value); }

void AnalogIn::setPinA(uint8_t pinA) { this->pinA = pinA; }

void AnalogIn::setPinB(uint8_t pinB) { this->pinB = pinB; }

void AnalogIn::setDevice(device_t device) { this->device = device; }

void AnalogIn::setResolution(uint8_t resolution) { 
    /* Managing the critical cases. */
    if (getDevice() == AIO_POTENTIOMETER) {
        if ((resolution > 10) && (resolution <= 12)) {
            /* Checking if the board is DUE, ZERO, MKR or ESP32 family. */
            #if defined(ARDUINO_ARCH_SAM) || defined(ARDUINO_ARCH_SAMD) || defined(ARDUINO_ARCH_ESP32)
                analogReadResolution((uint8_t) resolution);
            #else
                resolution = 10;
            #endif
        } else if (resolution > 12) {
            resolution = 10;
        }
    } else if (getDevice() == AIO_ENCODER) {
        if (resolution > AIO_MAX_BIT) {
            resolution = AIO_MAX_BIT;
        }
    }

    this->resolution = resolution; 
}

void AnalogIn::setMaxValue(int32_t maxValue) { this->maxValue = maxValue; }

void AnalogIn::setEmulatePinA(bool status) { this->emulatePinA = status; }

void AnalogIn::setEmulatePinB(bool status) { this->emulatePinB = status; }

uint8_t AnalogIn::getPinA() { return this->pinA; }

uint8_t AnalogIn::getPinB() { return this->pinB; }

device_t AnalogIn::getDevice() { return this->device; }

uint8_t AnalogIn::getResolution() { return this->resolution; }

bool AnalogIn::getEmulatePinA() { return this->emulatePinA; }

bool AnalogIn::getEmulatePinB() { return this->emulatePinB; }