#include "MainPage.h"

MainPage::MainPage(U8G2_SSD1306_128X64_NONAME_F_HW_I2C* objScreen, ProfileController* objProfile) {
  this->objScreen = objScreen;
  this->objProfile = objProfile; 

  setIsBluetoothActive(false);
  setIsWifiActive(false);

  deactivateBanner();
}

void MainPage::setIsBluetoothActive(bool flagBluetooth) { this->connectionsFlags.isBluetoothActive = flagBluetooth; }

void MainPage::setIsWifiActive(bool flagWifi) { this->connectionsFlags.isWifiActive = flagWifi; }

void MainPage::setIsBannerActive(bool isActive) { this->banner.isActive = isActive; }

void MainPage::setBannerEndTimeout(unsigned long endTimeout) { this->banner.endTimeout = endTimeout; }

void MainPage::setBannerText(String text) { this->banner.text = text; }

bool MainPage::getIsBluetoothActive() { return this->connectionsFlags.isBluetoothActive; }

bool MainPage::getIsWifiActive() { return this->connectionsFlags.isWifiActive; }

bool MainPage::getIsBannerActive() { return this->banner.isActive; }

unsigned long MainPage::getBannerEndTimeout() { return this->banner.endTimeout; }

String MainPage::getBannerText() { return this->banner.text; }

void MainPage::activateBanner(String text) {
  if (this->objScreen != NULL) {
    setIsBannerActive(true);
    setBannerEndTimeout(timeoutBanner + millis());
    setBannerText(text);
  }
}

void MainPage::deactivateBanner() {
  if (this->objScreen != NULL) {
    setIsBannerActive(false);
    setBannerEndTimeout(0);
    setBannerText("");
  }
}

void MainPage::show() {
  if ((this->objScreen != NULL) && (this->objProfile != NULL)) {
    if (this->objProfile->getIsOn()) {
      this->objScreen->firstPage();
      do {
        drawNotificationArea();
        drawInformationArea();
        
        if (banner.isActive && (millis() <= banner.endTimeout)) {
          drawBanner(); 
        } else if (banner.isActive && (millis() > banner.endTimeout)) {
          deactivateBanner();
        }
      } while (this->objScreen->nextPage());
    } else {
      this->objScreen->clear();
    }
  }
}

void MainPage::drawNotificationArea() {
  if (!objProfile->getError()) {
    /* Profile icon. */
    this->objScreen->setFont(u8g2_font_open_iconic_human_1x_t);
    this->objScreen->drawGlyph(positionIconProfile[0], positionIconProfile[1], 0x0044); 

    /* Profile name. */
    this->objScreen->setFont(u8g2_font_6x12_mf);
    this->objScreen->setCursor(positionLabelProfile[0], positionLabelProfile[1]);
    this->objScreen->print(this->objProfile->getNameProfile());
  }

  if (getIsWifiActive()) {
    /* WiFi icon. */
    this->objScreen->setFont(u8g2_font_open_iconic_www_1x_t);
    this->objScreen->drawGlyph(positionIconWiFi[0], positionIconWiFi[1], 0x0051);	
  }
  
  if (getIsBluetoothActive()) {
    /* Bluetooth icon. */
    this->objScreen->setFont(u8g2_font_open_iconic_embedded_1x_t);
    this->objScreen->drawGlyph(positionIconBluetooth[0], positionIconBluetooth[1], 0x004A); 
  }

  /* Line separator. */
  this->objScreen->drawHLine(lineSeparator[0], lineSeparator[1], lineSeparator[2]);
}

void MainPage::drawInformationArea() {
  /* This varfiabile contains the with fill, calulated with map function. */
  uint8_t widthFill;

  /* Array of 4 values, got from the profile method. */ 
  uint8_t* BRGB = this->objProfile->getValues();
  uint8_t* resolutions = this->objProfile->getResolutionsIn();

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
  
  /* Dynamic frame buffer for brightness. */
  widthFill = map(BRGB[0], 0, (long) pow(2, (double) resolutions[0]), 0, sizeFrameValues[0]);
  this->objScreen->drawFrame(positionFrameBrightness[0], positionFrameBrightness[1], sizeFrameValues[0], sizeFrameValues[1]);
  this->objScreen->drawBox(positionFrameBrightness[0], positionFrameBrightness[1], widthFill, sizeFrameValues[1]);

  /* Dynamic frame buffer for red. */
  widthFill = map(BRGB[1], 0, (long) pow(2, (double) resolutions[1]), 0, sizeFrameValues[0]);
  this->objScreen->drawFrame(positionFrameRed[0], positionFrameRed[1], sizeFrameValues[0], sizeFrameValues[1]);
  this->objScreen->drawBox(positionFrameRed[0], positionFrameRed[1], widthFill, sizeFrameValues[1]);

  /* Dynamic frame buffer for green. */
  widthFill = map(BRGB[2], 0, (long) pow(2, (double) resolutions[2]), 0, sizeFrameValues[0]);
  this->objScreen->drawFrame(positionFrameGreen[0], positionFrameGreen[1], sizeFrameValues[0], sizeFrameValues[1]);
  this->objScreen->drawBox(positionFrameGreen[0], positionFrameGreen[1], widthFill, sizeFrameValues[1]);

  /* Dynamic frame buffer for blue. */
  widthFill = map(BRGB[3], 0, (long) pow(2, (double) resolutions[3]), 0, sizeFrameValues[0]);
  this->objScreen->drawFrame(positionFrameBlue[0], positionFrameBlue[1], sizeFrameValues[0], sizeFrameValues[1]);
  this->objScreen->drawBox(positionFrameBlue[0], positionFrameBlue[1], widthFill, sizeFrameValues[1]);

  /* Values. */
  this->objScreen->setFont(u8g2_font_6x10_mf);
  this->objScreen->setDrawColor(colorValues);
  this->objScreen->setCursor(positionValueBrightness[0], positionValueBrightness[1]);
  this->objScreen->print(BRGB[0]);
  this->objScreen->setCursor(positionValueRed[0], positionValueRed[1]);
  this->objScreen->print(BRGB[1]);
  this->objScreen->setCursor(positionValueGreen[0], positionValueGreen[1]);
  this->objScreen->print(BRGB[2]);
  this->objScreen->setCursor(positionValueBlue[0], positionValueBlue[1]);
  this->objScreen->print(BRGB[3]);

  delete BRGB;
  delete resolutions;
}

void MainPage::drawBanner() {
  uint8_t indexStart = 0;
  uint8_t indexEnd = maxCharsBanner;
  uint8_t rowBanner = 0;

  String subText = getBannerText().substring(indexStart, indexEnd);

  this->objScreen->setDrawColor(colorInnerFrameBanner);
  this->objScreen->drawBox(positionFrameBanner[0], positionFrameBanner[1], sizeFrameBanner[0], sizeFrameBanner[1]);
  this->objScreen->setDrawColor(colorOuterFrameBanner);
  this->objScreen->drawFrame(positionFrameBanner[0], positionFrameBanner[1], sizeFrameBanner[0], sizeFrameBanner[1]);

  this->objScreen->setFont(u8g2_font_6x10_mf);
  this->objScreen->setCursor(positionLabelBanner[0], positionLabelBanner[1]);
  this->objScreen->print(subText);

  while ((getBannerText().substring(indexStart).length() > maxCharsBanner) || (rowBanner < maxRowBanner)) {
    rowBanner++; 
    this->objScreen->setCursor(positionLabelBanner[0], (rowBanner * 9) + positionLabelBanner[1]);

    indexStart = indexEnd;  
    if (getBannerText().substring(indexStart).length() < maxCharsBanner) {
      indexEnd = getBannerText().length();
    } else {
      indexEnd = indexStart + maxCharsBanner;
    }

    do {
      indexStart++;
      indexEnd++;
    } while (getBannerText().charAt(indexStart) == ' ');

    if ((getBannerText().charAt(indexEnd + 1) != ' ') && (getBannerText().substring(indexStart).length() > maxCharsBanner)) {
      do {
        indexEnd--;

        if (indexEnd == indexStart) {
          indexEnd = indexStart + maxCharsBanner;
          break;
        }
        
      } while (getBannerText().charAt(indexEnd) != ' ');      
    }

    subText = getBannerText().substring(indexStart, indexEnd);
    this->objScreen->print(subText);
  }
}