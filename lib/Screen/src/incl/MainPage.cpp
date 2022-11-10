#include "MainPage.h"

MainPage::MainPage(U8G2_SSD1306_128X64_NONAME_F_HW_I2C* objScreen) {
  this->objScreen = objScreen;
  setIsBluetoothActive(false);
}

void MainPage::setIsBluetoothActive(bool flagBluetooth) { this->isBluetoothActive = flagBluetooth; }

bool MainPage::getIsBluetoothActive() { return this->isBluetoothActive; }

void MainPage::show(uint8_t red, uint8_t green, uint8_t blue) {
  if ((this->objScreen != NULL)) {
      this->objScreen->firstPage();
      do {
        drawNotificationArea();
        drawInformationArea(uint8_t red, uint8_t green, uint8_t blue);
      } while (this->objScreen->nextPage());
    } else {
      this->objScreen->clear();
    }
}

void MainPage::drawNotificationArea() {
  if (getIsBluetoothActive()) {
    /* Bluetooth icon. */
    this->objScreen->setFont(u8g2_font_open_iconic_embedded_1x_t);
    this->objScreen->drawGlyph(positionIconBluetooth[0], positionIconBluetooth[1], 0x004A); 
  }

  /* Line separator. */
  this->objScreen->drawHLine(lineSeparator[0], lineSeparator[1], lineSeparator[2]);
}

void MainPage::drawInformationArea(uint8_t red, uint8_t green, uint8_t blue) {
  /* This variable contains the with fill, calculated with map function. */
  uint8_t widthFill;

  /* Name of knobs. */
  this->objScreen->setFont(u8g2_font_6x10_mf);
  this->objScreen->setCursor(positionLabelBrightness[0], positionLabelBrightness[1]);
  this->objScreen->print(labelValues[0]);
  this->objScreen->setCursor(positionLabelRed[0], positionLabelRed[1]);
  this->objScreen->print(labelValues[1]);
  this->objScreen->setCursor(positionLabelGreen[0], positionLabelGreen[1]);
  this->objScreen->print(labelValues[2]);
  this->objScreen->setCursor(positionLabelBlue[0], positionLabelBlue[1]);
  this->objScreen->print(labelValues[3]);
  
  /* Dynamic frame buffer for red. */
  widthFill = map(red, 0, 255, 0, sizeFrameValues[0]);
  this->objScreen->drawFrame(positionFrameRed[0], positionFrameRed[1], sizeFrameValues[0], sizeFrameValues[1]);
  this->objScreen->drawBox(positionFrameRed[0], positionFrameRed[1], widthFill, sizeFrameValues[1]);

  /* Dynamic frame buffer for green. */
  widthFill = map(green, 0, 255, 0, sizeFrameValues[0]);
  this->objScreen->drawFrame(positionFrameGreen[0], positionFrameGreen[1], sizeFrameValues[0], sizeFrameValues[1]);
  this->objScreen->drawBox(positionFrameGreen[0], positionFrameGreen[1], widthFill, sizeFrameValues[1]);

  /* Dynamic frame buffer for blue. */
  widthFill = map(blue, 0, 255, 0, sizeFrameValues[0]);
  this->objScreen->drawFrame(positionFrameBlue[0], positionFrameBlue[1], sizeFrameValues[0], sizeFrameValues[1]);
  this->objScreen->drawBox(positionFrameBlue[0], positionFrameBlue[1], widthFill, sizeFrameValues[1]);

  /* Values. */
  this->objScreen->setFont(u8g2_font_6x10_mf);
  this->objScreen->setDrawColor(colorValues);
  this->objScreen->setCursor(positionFrameRed[0], positionValueRed[1]);
  this->objScreen->print(red);
  this->objScreen->setCursor(positionValueGreen[0], positionValueGreen[1]);
  this->objScreen->print(green);
  this->objScreen->setCursor(positionValueBlue[0], positionValueBlue[1]);
  this->objScreen->print(blue);
}