#include "Profile.h"

uint8_t Profile::pinCS = 0;

Profile::Profile(String nameProfile, String directory, String fileName) {
    setNameProfile(nameProfile);
    setDirectory(directory);
    setFileName(fileName);
}

void Profile::setNameProfile(String nameProfile) { this->nameProfile = nameProfile; }

void Profile::setDirectory(String directory) { this->directory = directory; }

void Profile::setFileName(String fileName) { this->fileName = fileName; }

void Profile::setPinCS(uint8_t pin) { pinCS = pin; }

String Profile::getNameProfile() { return this->nameProfile; }

String Profile::getDirectory() { return this->directory; }

String Profile::getFileName() { return this->fileName; }

uint8_t Profile::getPinCS() { return pinCS; }

uint8_t* Profile::readFile() throw(uint8_t) {
    /* Connecting to SD card reader. Will be created an exception if there is some error during this operation. */
    if (!SD.begin(getPinCS())) {
      throw (uint8_t) 0;
    }

    /* Creating an array to contains the values read. */
    byte* values = new byte[4];

    /* Creating the object file. */
    File myFile = SD.open(getDirectory() + getFileName());

    /* Reading the values. Will be created an exception if there is some error during this operation. */
    if (!myFile) {
        throw (uint8_t) 1;
    }
    myFile.read(values, 4);
    myFile.close();
    SD.end();

    return values;
}

void Profile::writeFile(const uint8_t values[4]) throw(uint8_t) {
    /* Connecting to SD card reader. Will be created an exception if there is some error during this operation. */
    if (!SD.begin(getPinCS())) {
      throw (uint8_t) 0;
    }

    /* Checking if "nameFile" is already exists and in this case will be deleted. */
    if (SD.exists(getDirectory() + getFileName())) {
        SD.remove(getDirectory() + getFileName());
    }

    /* Creating the object file. */
    File myFile = SD.open(getDirectory() + getFileName(), FILE_WRITE);

    /* Writing the values. Will be created an exception if there is some error during this operation. */
    if (!myFile) {
        throw (uint8_t) 1;
    } 
    myFile.write(values, 4);
    myFile.close();
    SD.end();
}