#include "ProfileController.h"

ProfileController::ProfileController(AnalogController* objBrightness, AnalogController* objRed, AnalogController* objGreen, AnalogController* objBlue) {
    this->objBrightness = objBrightness;
    this->objRed = objRed;
    this->objGreen = objGreen;
    this->objBlue = objBlue;
}

void ProfileController::setProfile(Profile* objProfile) { this->objProfile = objProfile; }

void ProfileController::setValues(const uint8_t values[4]) {
    /* Setting the values. */
    this->objBrightness->setValue(values[0]);
    this->objRed->setValue(values[1]);
    this->objGreen->setValue(values[2]);
    this->objBlue->setValue(values[3]);

    /* Setting "isOn" if the brightness value is greater than 0 or not. */
    if (values[0] > 0) {
        setIsOn(true);
    } else {
        setIsOn(false);
    }
}

Profile* ProfileController::getProfile() { return this->objProfile; }

bool ProfileController::getIsOn() { return this->isOn; }

bool ProfileController::getError() { return this->error; }

String ProfileController::getNameProfile() { return this->objProfile->getNameProfile(); }

uint8_t* ProfileController::getValues() {
    uint8_t* values = new uint8_t[4];

    values[0] = this->objBrightness->getValue();
    values[1] = this->objRed->getValue(); 
    values[2] = this->objGreen->getValue(); 
    values[3] = this->objBlue->getValue();

    return values;
}

uint8_t* ProfileController::getResolutionsIn() {
    uint8_t* values = new uint8_t[4];

    values[0] = this->objBrightness->getResolutionIn();
    values[1] = this->objRed->getResolutionIn();
    values[2] = this->objGreen->getResolutionIn();
    values[3] = this->objBlue->getResolutionIn(); 

    return values;
}

uint8_t* ProfileController::getResolutionsOut() {
    uint8_t* values = new uint8_t[4];

    values[0] = this->objBrightness->getResolutionOut();
    values[1] = this->objRed->getResolutionOut();
    values[2] = this->objGreen->getResolutionOut();
    values[3] = this->objBlue->getResolutionOut(); 
    
    return values;
}

void ProfileController::readFile() throw(uint8_t) {
    /* Creating an array for contains the values read. */
    uint8_t* values;

    /* Trying the operation of reading and in case of failure will be propagated the exception. */
    try {
        values = objProfile->readFile();
        setValues(values);
        free(values);

        setError(false);
    } catch (uint8_t error) {
        setError(true);

        throw;
    } 
}

void ProfileController::writeFile() throw(uint8_t) {
    /* Creating an array for contains the values to write. */
    uint8_t* values;

    /* Trying the operation of writing and in case of failure will be propagated the exception. */
    try {
        values = getValues();
        objProfile->writeFile(values);
        free(values);

        setError(false);
    } catch (uint8_t error) {
        setError(true);

        throw;
    }
}

uint8_t ProfileController::readDevice() {
    /* Creating a variable to indicate is there is a change or not. */
    bool isChanged = false;

    /* Creating an array for contains the actual values. */
    uint8_t* values = getValues();

    /* Reading the new values from devices. */
    this->objBrightness->readValue();
    this->objRed->readValue();
    this->objGreen->readValue();
    this->objBlue->readValue();

    /* Checking if there is a change. */
    if ((values[0] != this->objBrightness->getValue()) || (values[1] != this->objRed->getValue()) || (values[2] != this->objGreen->getValue()) || (values[3] != this->objBlue->getValue())) {        
        /* Setting "isOn" if the brightness value is greater than 0 or not. */
        if (this->objBrightness->getValue() > 0) {
            setIsOn(true);
        } else {
            setIsOn(false);
        }
        
        isChanged = true;
    } else {
        isChanged = false;
    }

    free(values);

    if (isChanged) {
        return 1;
    } else {
        return 0;
    }
}

void ProfileController::writeDevice() {
    double percent = (this->objBrightness->getValue() * 100) / this->objBrightness->getMaxValueIn();

    this->objRed->writeValue(percent);
    this->objGreen ->writeValue(percent);
    this->objBlue->writeValue(percent);
}

void ProfileController::switchOnOff() {
    uint8_t* values = getValues();

    if (getIsOn()) {
        setIsOn(false);
        setBrightnesValue(values[0]);
        values[0] = 0;
    } else {
        setIsOn(true);
        values[0] = getBrightnesValue();
    }
    setValues(values);

    free(values);
}

void ProfileController::setIsOn (bool isOn) { this->isOn = isOn; }

void ProfileController::setError (bool error) { this->error = error; }

void ProfileController::setBrightnesValue(uint8_t brightnessValue) { this->brightnesValue = brightnessValue; }

uint8_t ProfileController::getBrightnesValue() { return this->brightnesValue; }