
#include "Arduino.h"
#include "String.h"

#include "USBSerialToStringLine.h"
#include "StructUtility.h"
#include "StructUtility.cpp"
#include "LogStruct.cpp"
#include "ExecuteStruct.h"
#include "ConvertStringToStruct.cpp"
#include "PushStringForTDD.cpp"

void setup() {
  Serial.begin(115200);
  Serial.print("Hello Boys !!!");
  // for debug
  while (!Serial); 
  TDD_Workspace();
}

String sString = "";
void loop() {
  //Current standar attempt
  //https://github.com/EloiStree/2022_06_17_HelloBLEMIDI/edit/main/Note/2022_07_03_WhatCanWePushWithLeonardo.md

  while (Serial.available()) {
    char c = Serial.read();
    sString += c;
    if (c == '\n') {
      PushLineWithDelay(sString);
      sString = "";
    }
  }
    bool found =false;
  // MidiAction action =  MidiAction();
  // TryConvertToMidi(&found, &action);
  
  // Serial.print("Midi:");
  // Serial.print(found);
  // Serial.print(",");
  // Serial.print(action.note);
  // Serial.print(",");
  // Serial.print(action.velocity);
  // Serial.print(",");
  // Serial.print(action.channel);
  // Serial.println("");

  delay(50);
  Serial.print(".");
}

