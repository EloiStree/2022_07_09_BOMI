#include "Arduino.h"
#include <SoftwareSerial.h>
#include "USBSerialToStringLine.h"
#include "SerialLog.cpp"


USBSerialToStringLine::USBSerialToStringLine(){

}

void USBSerialToStringLine::Init(uint8_t tx, uint8_t rx, int baud = 9600) {
  RxD = rx;
  TxD = tx;
  TargetSerial = new SoftwareSerial(RxD, TxD, false);
  Serial.begin(baud);
  pinMode(RxD, INPUT);
  pinMode(TxD, OUTPUT);
  TargetSerial->begin(baud);
}
bool USBSerialToStringLine::CheckForAvailable() {
  char recvChar;
  newCharFound = false;
  newLineFound = false;
  if (TargetSerial->available()) {
    newCharFound = true;
    recvChar = TargetSerial->read();
    received += recvChar;
    if (recvChar == '\n') {
      newLineFound = true;
      lineFound = received;
      received = "";

      // LogPrint("Line found:");
      // LogPrintLn(lineFound);
    } else {
      // LogPrint("Append:");
      // LogPrintLn(received);
    }
  }
  return newLineFound;
}
void USBSerialToStringLine::DisplayStateIfChanged() {
  if (newCharFound) {
    if (newLineFound){
      LogPrint("Line found:"); 
      LogPrintLn(lineFound);
    }
    else{
      LogPrint("Append:");
      LogPrintLn(received);
    }
  }
}

bool USBSerialToStringLine::HasNewLine() {
  return newLineFound;
}
String USBSerialToStringLine::GetPreviousLine() {
  return lineFound;
}
String USBSerialToStringLine::GetCurrentStack() {
  return received;
}