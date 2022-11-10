#include "AddressableStrip.h"

AddressableStrip::AddressableStrip(uint8_t pinData, uint8_t nLed, ProfileController* objProfile) {
    this->objLed = new NeoPixelBus<NeoGrbwFeature, Neo800KbpsMethod>(nLed, pinData);
    this->objProfile = objProfile;

    this->objColorsPowerOn = new RgbwColor(colorsPowerOn[0], colorsPowerOn[1], colorsPowerOn[2], colorsPowerOn[3]);
    this->objColorsStandby = new RgbwColor(colorsStandby[0], colorsStandby[1], colorsStandby[2], colorsStandby[3]);
    this->objColorsError = new RgbwColor(colorsError[0], colorsError[1], colorsError[2], colorsStandby[3]);
}

void AddressableStrip::begin() { this->objLed->Begin(); }

void AddressableStrip::show() {
    if (!objProfile->getError()) {
        if (objProfile->getIsOn()) {
            populateAllLed(this->objColorsPowerOn);
        } else {
            populateAllLed(this->objColorsStandby);
        }
    } else {
        populateAllLed(this->objColorsError);
    }
    this->objLed->Show();
}

void AddressableStrip::populateAllLed(RgbwColor* objColors) {
    for (uint8_t led = 1; led <= objLed->PixelCount(); led++) {
        objLed->SetPixelColor((led - 1), *objColors);
    }
}