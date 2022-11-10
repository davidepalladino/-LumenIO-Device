#include "AnalogOut.h"

AnalogOut::AnalogOut(uint8_t pin) : AnalogOut(pin, 8) {}

AnalogOut::AnalogOut(uint8_t pin, uint8_t resolution) {
    setPin(pin);
    pinMode(getPin(), OUTPUT);

    setResolution(resolution);

    setMaxValue((uint16_t) (pow(2, getResolution()) - 1));
}

uint16_t AnalogOut::getMaxValue() { return this->maxValue; }

uint16_t AnalogOut::write(uint16_t value) {
    /* Checking if the value is greater than "maxValue", by setting it if so. */
    if (value > getMaxValue()) {
        value = getMaxValue();
    }

    /* Normalizing the value if it is less than . */
    if (getMaxValue() < AIO_MAX_VALUE_BIT8) {
        value = map(value, 0, AIO_MAX_VALUE_BIT8, 0, getMaxValue());
    }
    
    analogWrite(getPin(), value);

    return value;
}

void AnalogOut::setPin(uint8_t pin) { this->pin = pin; }

void AnalogOut::setResolution(uint8_t resolution) { 
    /* Managing the critical cases. */
    if ((resolution > 10) && (resolution <= 12)) {
        /* Checking if the board is DUE, ZERO or MKR family. */
        #if defined(ARDUINO_ARCH_SAM) || defined(ARDUINO_ARCH_SAMD) || defined(ARDUINO_ARCH_ESP32)
            analogWriteResolution((uint8_t) resolution);
        #else
            resolution = 8;
        #endif
    } else if ((resolution > 12) || (resolution == 0)) {
        resolution = 8;
    }

    this->resolution = resolution; 
}

void AnalogOut::setMaxValue(uint16_t maxValue) { this-> maxValue = maxValue; }

uint8_t AnalogOut::getPin() { return this->pin; }

uint8_t AnalogOut::getResolution() { return this->resolution; }