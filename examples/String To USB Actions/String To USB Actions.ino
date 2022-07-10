#include "Arduino.h"
#include "USBSerialToStringLine.h"
#include "IR2Midi.h"
#include "DigitAndAnalogAsBoolean.h"
#include "SerialLog.h"
#include "SerialLog.cpp"
#include "ConvertStringToStruct.h"
#include "ConvertStringToStruct.cpp"
//#include "SerialLog/SerialLog.cpp"

USBSerialToStringLine BT;
IR2Midi irToMidi;

bool m_useDelayToDebug = false;
bool m_writeMidiCodeWithNumPad = true;

ListenPinsAsBoolean pinsAsBoolean;
int useMidiAsKeyboardPin = 2;

void setup() {
  SetSerialLog(true);
  //serialRead = new USBSerialToStringLine();
  BT.Init(10, 11, 115200);
  irToMidi.InitIR();
  Serial.print("Hello Boys !!!");
  pinMode(useMidiAsKeyboardPin, INPUT_PULLUP);

  pinsAsBoolean.InitDefault();
  pinsAsBoolean.RefreshPinMode();
  ////SETUP
  ////SETUP
}
String sString = "";
void loop() {

  m_writeMidiCodeWithNumPad = digitalRead(useMidiAsKeyboardPin) != HIGH;
  sString = "";
  if (BT.CheckForAvailable()) {
    // BT.DisplayStateIfChanged();
    String line = BT.GetPreviousLine();
    PushLine(line);
  }
  while (Serial.available()) {
    char c = Serial.read();
    sString += c;
    if (c == '\n') {
      PushLine(sString);
      sString = "";
    }
  }

  irToMidi.ReadAndConvertToMidi();
  if (irToMidi.HasReceivedIR()) {
    irToMidi.DisplayPreviousIRToMidiIfFound();
    String toPush = "M:";
    toPush += irToMidi.m_peviousNote;
    toPush += ",";
    toPush += irToMidi.m_peviousVelocity;
    toPush += ",";
    toPush += irToMidi.m_peviousChannel;
    PushLine(toPush);
  }


  //PIN BOOLEAN TO ACTION
  pinsAsBoolean.UpdatePinInfoIfNotZero();
  pinsAsBoolean.DisplayOnSerialChangedInput(false);
  for (int i = 0; i < pinsAsBoolean.digitalBoolCount; i++) {
    if (!pinsAsBoolean.digitalBool[i].IsPinZero() && pinsAsBoolean.digitalBool[i].HasChangedThisFrame()) {
      PushLineMidi(
        pinsAsBoolean.digitalBool[i].IsCurrentOn(), 50 + pinsAsBoolean.digitalBool[i].m_pinId, 126, 2);
    }
  }
  for (int i = 0; i < pinsAsBoolean.analogBoolCount; i++) {
    if (!pinsAsBoolean.analogBool[i].IsPinZero() && pinsAsBoolean.analogBool[i].HasChangedThisFrame()) {
      PushLineMidi(pinsAsBoolean.analogBool[i].IsCurrentOn(), 100 + pinsAsBoolean.analogBool[i].m_pinId, 126, 2);
    }
  }
  //PIN BOOLEAN TO ACTION
   Serial.print(".");
   delay(100);
}

void PushLineMidi(byte note, byte velocity, byte channel) {
  PushLineMidi(true, note, velocity, channel);
  PushLineMidi(false, note, velocity, channel);
}
void PushLineMidi(bool press, byte note, byte velocity, byte channel) {
  String toPush = press ? "MP:" : "MR:";
  toPush += note;
  toPush += ",";
  toPush += velocity;
  toPush += ",";
  toPush += channel;
  PushLine(toPush);
}
void PushLine(String line) {
  LogPrintDoubleLn("Found Line:",line);
  //delay(3000);
  TryConvertAndExecute(line);
  LogPrintLn("Sent");
  
}