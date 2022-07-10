#ifdef BLEPushHH
#else


#include "Arduino.h"
#include "String.h"
#include "StructUtility.h"
#include "ExecuteStruct.h"
#include "LogStruct.cpp"
#include "SerialLog.cpp"

#include <SPI.h>
#include "Adafruit_BLE.h"
#include "Adafruit_BluefruitLE_SPI.h"
#include "Adafruit_BluefruitLE_UART.h"
#include "BluefruitConfig.h"
#define FACTORYRESET_ENABLE 0
#define MINIMUM_FIRMWARE_VERSION_KEYBOARD "0.6.6"

static const Adafruit_BluefruitLE_SPI ble(BLUEFRUIT_SPI_CS, BLUEFRUIT_SPI_IRQ, BLUEFRUIT_SPI_RST);
static const int timeBetweenPressRelease = 10;


class BLEPush{
  public:
  BLEPush();
  void BLE_Setup(bool initSerial) ;
  void BLE_Loop();
  void GetUserInput(char buffer[], uint8_t maxSize) ;
  void PrintTextToKeyoard(String text);
  void Error(const __FlashStringHelper* err);
};


/////////////////////////////////////// BLE //////////////

#endif