#ifdef BLEPUSHCPP
#else


#include "Arduino.h"
#include "String.h"
#include "StructUtility.h"
#include "ExecuteStruct.h"
#include "LogStruct.cpp"
#include "SerialLog.cpp"

#include "BLEPush.h"
#include <SPI.h>
#include "Adafruit_BLE.h"
#include "Adafruit_BluefruitLE_SPI.h"
#include "Adafruit_BluefruitLE_UART.h"
#include "BluefruitConfig.h"
#define FACTORYRESET_ENABLE 0
#define MINIMUM_FIRMWARE_VERSION_KEYBOARD "0.6.6"
// Adafruit_BluefruitLE_SPI ble(BLUEFRUIT_SPI_CS, BLUEFRUIT_SPI_IRQ, BLUEFRUIT_SPI_RST);
// static const int timeBetweenPressRelease = 10;

/////////////////////////////////////// BLE ///////////////

 BLEPush::BLEPush(){

}

 void BLEPush::Error(const __FlashStringHelper* err) {
  Serial.println(err);
  while (1)
    ;
}
 void  BLEPush::BLE_Setup(bool initSerial) {
  if (initSerial) {
    Serial.begin(115200);
  }

  if (!ble.begin(VERBOSE_MODE))
    Error(F("Couldn't find Bluefruit, make sure it's in CoMmanD mode & check wiring?"));

  if (FACTORYRESET_ENABLE && !ble.factoryReset())
    Error(F("Couldn't factory reset"));

  ble.echo(false);
  ble.info();

  if (!ble.sendCommandCheckOK(F("AT+GAPDEVNAME=E Bluefruit Keyboard")))
    Error(F("Could not set device name?"));
  if (ble.isVersionAtLeast(MINIMUM_FIRMWARE_VERSION_KEYBOARD)) {
    if (!ble.sendCommandCheckOK(F("AT+BleHIDEn=On")))
      Error(F("Could not enable Keyboard"));

  } else {
    if (!ble.sendCommandCheckOK(F("AT+BleKeyboardEn=On")))
      Error(F("Could not enable Keyboard"));
  }
  if (!ble.sendCommandCheckOK(F("ATZ")))
    Error(F("Could not enable Keyboard"));
  if (!ble.reset()) {
    Error(F("Couldn't reset??"));
  }
}


 void  BLEPush::GetUserInput(char buffer[], uint8_t maxSize) {
  memset(buffer, 0, maxSize);
  while (Serial.available() == 0) {
    delay(1);
  }

  uint8_t count = 0;

  do {
    count += Serial.readBytes(buffer + count, maxSize);
    delay(2);
  } while ((count < maxSize) && !(Serial.available() == 0));
}



 void  BLEPush::PrintTextToKeyoard(String text) {

  ble.print("AT+BleKeyboard=");
  ble.println(text);
  if (ble.waitForOK()) {
    Serial.println(F("OK!"));
  } else {
    Serial.println(F("FAILED!"));
  }
}

 void  BLEPush::BLE_Loop() {
  Serial.print(F("keyboard > "));
  char keys[BUFSIZE + 1];
  GetUserInput(keys, BUFSIZE);

  Serial.print("\nSending ");
  Serial.println(keys);
  PrintTextToKeyoard(keys);
}

/////////////////////////////////////// BLE //////////////

#endif