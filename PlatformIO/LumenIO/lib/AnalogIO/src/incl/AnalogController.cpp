#include "AnalogController.h"

AnalogController::AnalogController(AnalogIn* objIn, AnalogOut* objOut){
    this->objIn = objIn;
    this->objOut = objOut;

    setValue(0);
}

void AnalogController::setValue(int32_t value) {
    /* Checking if the "objIn" exists, and in this case will be considered the max value, if the resolution is not equal to 0. */
    if (objIn != NULL) {
        if (objIn->getResolution() != NONE) {
            if (value < 0) {
                this->value = 0;
            } else if (value > getMaxValueIn()) {
                this->value = getMaxValueIn();
            } else {
                this->value = value;
            }
        } else {
            this->value = value;
        }
        objIn->objEncoder.setCount(this->value);        
    /* If the "objIn" doesn't exist, will be considered the "objOut". */
    } else if ((objIn == NULL) && (objOut != NULL)) {
        if (value < 0) {
            this->value = 0;
        } else if (value > getMaxValueOut()) {
            this->value = getMaxValueOut();
        } else {
            this->value = value;
        }
    }
}

int32_t AnalogController::getValue() { return this->value; }

void AnalogController::readValue() {
    if (objIn != NULL) {
        setValue(objIn->read());
    }
}

int32_t AnalogController::getMaxValueIn() {
    if (objIn != NULL) {
        return objIn->getMaxValue();
    } else {
        return 0;
    }
}

uint16_t AnalogController::getMaxValueOut() {
    if (objOut != NULL) {
        return objOut->getMaxValue();
    } else {
        return 0;
    }
}

int8_t AnalogController::getResolutionIn() {
    if (objIn != NULL) {
        return objIn->getResolution();
    } else {
        return -1;
    }
}

int8_t AnalogController::getResolutionOut() {
    if (objOut != NULL) {
        return objOut->getResolution();
    } else {
        return -1;
    }
}

uint16_t AnalogController::writeValue() {
    return writeValue(100);
}

uint16_t AnalogController::writeValue(double percent) {
    if (objOut != NULL) {
        int32_t valueTemp = getValue();

        /* Normalizing the value if the resolution is not similar between "objIn" and "objOut". */
        if ((objIn != NULL) && (objIn->getResolution() != NONE) && (objIn->getResolution() != objOut->getResolution())) {
            valueTemp = map((uint16_t) valueTemp, 0, getMaxValueIn(), 0, getMaxValueOut());
        /* Forcing the value to 0 or "maxValue" of "objOut", if the value is greater or less than them and the resolution of "objIn" is set to 0. */
        } else if ((objIn != NULL) && (objIn->getResolution() == NONE)) {
            if (valueTemp < 0) {
                valueTemp = 0;
            } else if (valueTemp > getMaxValueOut()) {
                valueTemp = getMaxValueOut();
            }
        }

        /* Correcting the "percent value" if is less than 0 or greater than 100. */
        if (percent < 0) {
            percent = 0;
        } else if (percent > 100) {
            percent = 100;
        }
        
        /* Calculating the percent, if is less than 100. */
        if (percent < 100) {
            valueTemp = ((double) valueTemp * percent) / 100;
        }

        return objOut->write((uint16_t) valueTemp);
    } else {
        return 0;
    }
}

void AnalogController::blink(uint8_t times, uint32_t timeOut) {
    if (objOut != NULL) {
        for (uint8_t t = 1; t <= times; t++) {
            objOut->write(getMaxValueOut());
            delay(timeOut);
            objOut->write(0);

            if(t < times) {
                delay(timeOut);
            }
        }    
    }
}