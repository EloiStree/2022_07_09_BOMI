#ifndef EXECUTE_CPP
#define EXECUTE_CPP
#include "Arduino.h"
#include "String.h"
#include "StructUtility.h"
#include "ExecuteStruct.h"
#include "LogStruct.cpp"
#include "SerialLog.cpp"
#include "Keyboard.h"
#include "USB/StringToUSBMIDI.h"
#include "USB/StringToUSBKeyboard.h"

StringToUSBMIDI MIDIT ;
StringToUSBKeyboard USBT;

#define KEY_LEFT_CTRL 0x80
#define KEY_LEFT_SHIFT 0x81
#define KEY_LEFT_ALT 0x82  //Option (⌥) on Mac
#define KEY_LEFT_GUI 0x83  //OS logo, Command (⌘) on Mac
#define KEY_RIGHT_CTRL 0x84
#define KEY_RIGHT_SHIFT 0x85
#define KEY_RIGHT_ALT 0x86  //also AltGr, Option (⌥) on Mac
#define KEY_RIGHT_GUI 0x87  //OS logo, Command (⌘) on Mac
#define KEY_KP_DOT 0xEB
#define KEY_NUM_LOCK 0xDB
#define KEY_KP_SLASH 0xDC
#define KEY_KP_ASTERISK 0xDD
#define KEY_KP_MINUS 0xDE
#define KEY_KP_PLUS 0xDF
#define KEY_KP_ENTER 0xE0
#define KEY_BACKSPACE 0xB2
#define KEY_TAB 0xB3
#define KEY_RETURN 0xB0
#define KEY_ESC 0xB1
#define KEY_MENU 0xED
#define KEY_INSERT 0xD1
#define KEY_DELETE 0xD4
#define KEY_CAPS_LOCK 0xC1
#define KEY_PAGE_UP 0xD3
#define KEY_PAGE_DOWN 0xD6
#define KEY_HOME 0xD2
#define KEY_END 0xD5
#define KEY_CAPS_LOCK 0xC1
#define KEY_MUTE 0x7F
#define KEY_VOLUMEUP 0x80
#define KEY_VOLUMEDOWN 0x81
#define KEY_PRINT_SCREEN 0xCE
#define KEY_SCROLL_LOCK 0xCF
#define KEY_PAUSE 0xD0
#define KEY_UP_ARROW 0xDA
#define KEY_DOWN_ARROW 0xD9
#define KEY_LEFT_ARROW 0xD8
#define KEY_RIGHT_ARROW 0xD7


static const int timeBetweenPressRelease = 10;
//https://www.arduino.cc/reference/en/language/functions/usb/keyboard/keyboardmodifiers/
static const int F1to24[]{ 0xC2, 0xC3, 0xC4, 0xC5, 0xC6, 0xC7, 0xC8, 0xC9, 0xCA, 0xCB, 0xCC, 0xCD, 0x68, 0x69, 0x6A, 0x6B, 0x6C, 0x6D, 0x6E, 0x6F, 0x70, 0x71, 0x72, 0x73 };
static const int NP0to9[]{ 0xEA, 0xE1, 0xE2, 0xE3, 0xE4, 0xE5, 0xE6, 0xE7, 0xE8, 0xE9 };
static const char Alpha0to9[]{ '0', '1', '2', '3', '4', '5', '6', '7', '8', '9' };


static const int IdOfArduinoModule(String text) {

  text.toUpperCase();
  text.trim();
  if (text.equals("KEY_LEFT_CTRL")) return (int)0x80;
  else if (text.equals("KEY_LEFT_SHIFT"))
    return (int)0x81;
  else if (text.equals("KEY_LEFT_ALT"))
    return (int)0x82;  //Option (⌥) on Mac
  else if (text.equals("KEY_LEFT_GUI"))
    return (int)0x83;  //OS logo, Command (⌘) on Mac
  else if (text.equals("KEY_RIGHT_CTRL"))
    return (int)0x84;
  else if (text.equals("KEY_RIGHT_SHIFT"))
    return (int)0x85;
  else if (text.equals("KEY_RIGHT_ALT"))
    return (int)0x86;  //also AltGr, Option (⌥) on Mac
  else if (text.equals("KEY_RIGHT_GUI"))
    return (int)0x87;  //OS logo, Command (⌘) on Mac
  else if (text.equals("KEY_KP_DOT"))
    return (int)0xEB;
  else if (text.equals("KEY_NUM_LOCK"))
    return (int)0xDB;
  else if (text.equals("KEY_KP_SLASH"))
    return (int)0xDC;
  else if (text.equals("KEY_KP_ASTERISK"))
    return (int)0xDD;
  else if (text.equals("KEY_KP_MINUS"))
    return (int)0xDE;
  else if (text.equals("KEY_KP_PLUS"))
    return (int)0xDF;
  else if (text.equals("KEY_KP_ENTER"))
    return (int)0xE0;
  else if (text.equals("KEY_BACKSPACE"))
    return (int)0xB2;
  else if (text.equals("KEY_TAB"))
    return (int)0xB3;
  else if (text.equals("KEY_RETURN"))
    return (int)0xB0;
  else if (text.equals("KEY_ESC"))
    return (int)0xB1;
  else if (text.equals("KEY_MENU"))
    return (int)0xED;
  else if (text.equals("KEY_INSERT"))
    return (int)0xD1;
  else if (text.equals("KEY_DELETE"))
    return (int)0xD4;
  else if (text.equals("KEY_CAPS_LOCK"))
    return (int)0xC1;
  else if (text.equals("KEY_PAGE_UP"))
    return (int)0xD3;
  else if (text.equals("KEY_PAGE_DOWN"))
    return (int)0xD6;
  else if (text.equals("KEY_HOME"))
    return (int)0xD2;
  else if (text.equals("KEY_END"))
    return (int)0xD5;
  else if (text.equals("KEY_CAPS_LOCK"))
    return (int)0xC1;
  else if (text.equals("KEY_MUTE"))
    return (int)0x7F;
  else if (text.equals("KEY_VOLUMEUP"))
    return (int)0x80;
  else if (text.equals("KEY_VOLUMEDOWN"))
    return (int)0x81;
  else if (text.equals("KEY_PRINT_SCREEN"))
    return (int)0xCE;
  else if (text.equals("KEY_SCROLL_LOCK"))
    return (int)0xCF;
  else if (text.equals("KEY_PAUSE"))
    return (int)0xD0;
  else if (text.equals("KEY_UP_ARROW"))
    return (int)0xDA;
  else if (text.equals("KEY_DOWN_ARROW"))
    return (int)0xD9;
  else if (text.equals("KEY_LEFT_ARROW"))
    return (int)0xD8;
  else if (text.equals("KEY_RIGHT_ARROW"))
    return (int)0xD7;
  return 0;
}

static const void PressionCharTargetKey(bool press, bool release, char key) {
  //LogPrint("Char key :");
  //LogPrint(press);
  //LogPrint(release);
  //LogPrint(key);
  //LogPrintLn();
  if (press)
    Keyboard.press(key);
  if (press && release)
    delay(timeBetweenPressRelease);
  if (release)
    Keyboard.release(key);
}

static const void Stroke(char key) {
  PressionCharTargetKey(true, true, key);
}
static const void Press(char key) {
  Keyboard.press(key);
}
static const void Release(char key) {
  Keyboard.release(key);
}
static const void PressionCharTargetKey(PressionRequest* pression, char key) {
  PressionCharTargetKey(pression->press, pression->release, key);
}


static const void PressionIntTargetKey(bool press, bool release, int key) {

  //LogPrint("Int key :");
  //LogPrint(press);
  //LogPrint(release);
  //LogPrint(key);
  //LogPrintLn();
  if (press)
    Keyboard.press(key);
  if (press && release)
    delay(timeBetweenPressRelease);
  if (release)
    Keyboard.release(key);
}
static const void Stroke(int key) {
  PressionIntTargetKey(true, true, key);
}
static const void Press(int key) {
  Keyboard.press(key);
}
static const void Release(int key) {
  Keyboard.release(key);
}
static const void PressionIntTargetKey(PressionRequest* pression, int key) {
  PressionIntTargetKey(pression->press, pression->release, key);
}



static const void KeyboardAsText(bool press, bool release, String text) {
  int isCommand = IdOfArduinoModule(text);
  if (isCommand > 0) {
    PressionIntTargetKey(press, release, isCommand);
  } else {
    //LogPrint("Print Keyboard:");
    //LogPrintLn(text);
    Keyboard.print(text);
  }
}
static const void KeyboardAsText(PressionRequest* pression, String text) {
  KeyboardAsText(pression->press, pression->release, text);
}


KeyboardExecutor::KeyboardExecutor() {

  // Keyboard.begin();
  // Keyboard.releaseAll();

  MIDIT.Init();
  USBT.Init();

}
void KeyboardExecutor::ExecuteKeyPressionAlt() {
  //LogPrint(" Press ALT  ");
  Press(KEY_LEFT_ALT);
}
void KeyboardExecutor::ExecuteKeyReleaseAlt() {
  //LogPrint("Release ALT  ");
  Release(KEY_LEFT_ALT);
}
void KeyboardExecutor::ExecuteKeyPressionCtrl() {
  //LogPrint(" Press CTRL  ");
  Press(KEY_LEFT_CTRL);
}
void KeyboardExecutor::ExecuteKeyReleaseCtrl() {
  //LogPrint(" Release CTRL  ");
  Release(KEY_LEFT_CTRL);
}
void KeyboardExecutor::ExecuteKeyPressionShift() {
  //LogPrint(" Press SHIFT  ");
  Press(KEY_LEFT_SHIFT);
}
void KeyboardExecutor::ExecuteKeyReleaseShift() {
  //LogPrint(" Release SHIFT  ");
  Release(KEY_LEFT_SHIFT);
}
void KeyboardExecutor::ExecuteKeyPressionEnter() {
  //LogPrint(" Press ENTER  ");
  Press(KEY_RETURN);
}
void KeyboardExecutor::ExecuteKeyReleaseEnter() {
  //LogPrint(" Release Enter  ");
  Release(KEY_RETURN);
}
void KeyboardExecutor::ExecuteKeyStrokeEnter() {
  //LogPrint(" Stroke Enter  ");
  Stroke(KEY_RETURN);
}
void KeyboardExecutor::ExecuteKeyStrokeTab() {
  //LogPrint(" Stroke tab  ");
  Stroke(KEY_TAB);
}
void KeyboardExecutor::ExecuteKeyStrokeBackspace() {
  //LogPrint(" Stroke backspace  ");
  Stroke(KEY_BACKSPACE);
}

void KeyboardExecutor::ExecuteNumpadDigit(PressionRequest* pression, char c) {
  //LogPrint(" NP  ");
  //LogPrint(c);
  //LogPrint(pression->press);
  //LogPrint(pression->release);
}
void KeyboardExecutor::ExecuteNumpadDigit(char c) {
  //LogPrint(" NP Stroke ");
  //LogPrint(c);
}
void KeyboardExecutor::ExecuteNumpadDigit(PressionRequest* pression, int index) {
  //LogPrint(" NP  ");
  //LogPrint(index);
  //LogPrint(pression->press);
  //LogPrint(pression->release);
}
void KeyboardExecutor::ExecuteNumpadDigit(int index) {
  //LogPrint(" NP Stroke ");
  //LogPrint(index);
}

void KeyboardExecutor::Execute(ParseStringToNumpadStrokeAction* toExecute) {
  //LogPrint(" Numpad(s) for string:");
  //LogPrintLn(toExecute->textToNumpad);
}
void KeyboardExecutor::ExecuteAsWindowUnicodeFromText(String unicodeAsText) {
  //LogPrint(" Unicode: ");
  //LogPrintLn(unicodeAsText);
}
void KeyboardExecutor::Execute(WindowUnicodeIntPrintAction* toExecute) {
  //LogPrint(" Unicode int:  ");
  //LogPrintLn(toExecute->unicodeIntId);
}
void KeyboardExecutor::Execute(WindowUnicodeStringPrintAction* toExecute) {
  //LogPrint(" Unicode string:  ");
  //LogPrintLn(toExecute->unicodeStringId);
}

void KeyboardExecutor::Execute(KeyboardStringPrintAction* toExecute) {
  //LogPrint("Keyboard:");
  //LogPrintLn(toExecute->toWrite);
  Keyboard.print(toExecute->toWrite);
}

void KeyboardExecutor::Execute(PressionRequest* pression, MidiAction* toExecute) {
  Log(pression, toExecute);
  MIDIT.NoteStroke(toExecute->note, toExecute->velocity, toExecute->channel, pression->press, pression->release );
}
void KeyboardExecutor::Execute(PressionRequest* pression, int hidUsbId) {
  //LogPrint(" Key HID :  ");
  //LogPrint(pression->press);
  //LogPrint(pression->release);
  //LogPrintLn(hidUsbId);
}

void KeyboardExecutor::Execute(PressionRequest* pression, KeyboardUSBIDAction* toExecute) {
  //LogPrint(" Key HID : ");
  //LogPrint(pression->press);
  //LogPrint(pression->release);
  //LogPrintLn(toExecute->id);
}
void KeyboardExecutor::Execute(PressionRequest* pression, KeyboardCharPrintAction* toExecute) {
  //LogPrint("CHAR Print:");
  //LogPrint(pression->press);
  //LogPrint(pression->release);
  //LogPrintLn(toExecute->toWrite);
}


void KeyboardExecutor::Execute(PressionRequest* pression, KeyboardCharTryToStrokeAction* toExecute) {

  //LogPrint("CHAR Stroke:");
  //LogPrint(pression->press);
  //LogPrint(pression->release);
  //LogPrintLn(toExecute->toStroke);
}

void KeyboardExecutor::Execute(PressionRequest* pression, KeyboardAlphaStroke* toExecute) {
  //LogPrint("\nAlpa Key:");
  //LogPrintLn(toExecute->numberToStroke0To9);
  if (toExecute->numberToStroke0To9 < 0 || toExecute->numberToStroke0To9 > 9)
    return;
  PressionCharTargetKey(pression, Alpha0to9[toExecute->numberToStroke0To9]);
}
void KeyboardExecutor::Execute(PressionRequest* pression, KeyboardNumpadStroke* toExecute) {

  //LogPrint("\Num Pad Key:");
  //LogPrintLn(toExecute->numberToStroke0To9);
  if (toExecute->numberToStroke0To9 < 0 || toExecute->numberToStroke0To9 > 9)
    return;
  PressionIntTargetKey(pression, NP0to9[toExecute->numberToStroke0To9]);
}







void KeyboardExecutor::Execute(PressionRequest* pression, KeyboardFunctionStroke* toExecute) {
  //LogPrint("\Func Key:");
  //LogPrintLn(toExecute->f1To24);
  if (toExecute->f1To24 < 1 || toExecute->f1To24 > 24)
    return;
  PressionIntTargetKey(pression, F1to24[(toExecute->f1To24) - 1]);
}

void KeyboardExecutor::Execute(PressionRequest* pression, KeyboardArrowType* toExecute) {
  //LogPrint(" Enum Keys:");
  //LogPrintLn(*toExecute);
}
void KeyboardExecutor::Execute(PressionRequest* pression, KeyboardNumpadType* toExecute) {
  //LogPrint(" Enum Numpad:");
  //LogPrintLn(*toExecute);
}
void KeyboardExecutor::Execute(PressionRequest* pression, KeyboardClassicKeyType* toExecute) {
  //LogPrint(" Enum Classic:");
  //LogPrintLn(*toExecute);
}

void KeyboardExecutor::Execute(PressionRequest* pression, SwitchPinIntMode* toExecute) {
  pinMode(toExecute->pinId, OUTPUT);

  digitalWrite(toExecute->pinId, pression->press ? LOW : HIGH);
  if (pression->press && pression->release) {
    delay(10);
  }
  digitalWrite(toExecute->pinId, pression->release ? LOW : HIGH);

  //LogPrint("Pin:");
  //LogPrintLn(toExecute->pinId);
}
void KeyboardExecutor::Execute(PressionRequest* pression, SwitchPinAsStringMode* toExecute) {
  String s = toExecute->pinIdAsString;
  s.toUpperCase();
  s.trim();
  int pinId = 0;
  if (s.equals("A0") || s.equals("0A")) pinId = A0;
  else if (s.equals("A1") || s.equals("1A"))
    pinId = A1;
  else if (s.equals("A2") || s.equals("2A"))
    pinId = A2;
  else if (s.equals("A3") || s.equals("3A"))
    pinId = A3;
  else if (s.equals("A4") || s.equals("4A"))
    pinId = A4;
  else if (s.equals("A5") || s.equals("5A"))
    pinId = A5;
  else if (s.equals("A6") || s.equals("6A"))
    pinId = A6;
  else if (s.equals("A7") || s.equals("7A"))
    pinId = A7;
  else
    pinId = s.toInt();
  pinMode(pinId, OUTPUT);
  digitalWrite(pinId, pression->press ? LOW : HIGH);
  if (pression->press && pression->release) {
    delay(10);
  }
  digitalWrite(pinId, pression->release ? LOW : HIGH);


  //LogPrint("Pin:");
  //LogPrintLn(pinId);
}




void KeyboardExecutor::Execute(PrintDefaultSerialText* toExecute) {
  //LogPrintLn(toExecute->textToPrint);
}
void KeyboardExecutor::Execute(TransitToAllSerialText* toExecute) {
  PrintDefaultSerialText* pt = new PrintDefaultSerialText();
  pt->textToPrint = toExecute->textToPrint;
  Execute(pt);

  TransitOnHCXXSerialText* hct = new TransitOnHCXXSerialText();
  hct->textToPrint = toExecute->textToPrint;
  Execute(hct);

  TransitOnBLESerialText* blet = new TransitOnBLESerialText();
  blet->textToPrint = toExecute->textToPrint;
  Execute(blet);
}

void KeyboardExecutor::Execute(TransitOnHCXXSerialText* toExecute) {

  //LogPrintLn("ADD CODE HERE:");
  //LogPrintLn(toExecute->textToPrint);
}
void KeyboardExecutor::Execute(TransitOnBLESerialText* toExecute) {

  //LogPrintLn("ADD CODE HERE:");
  //LogPrintLn(toExecute->textToPrint);
}
void KeyboardExecutor::Execute(KeyboardControlString* toExecute) {

  //LogPrintLn("ADD CODE HERE:");
  //LogPrint("Key Control:");
  //LogPrintLn(toExecute->stringKey);
}



static const void FA() {
  Serial.println("AAA");
}
static const void FB() {
  Serial.println("BBB");
}
static const void FC() {
  Serial.println("CCC");
}
static const void FD() {
  Serial.println("DDD");
}

void KeyboardExecutor::Execute(CallFunctionInArduino* toExecute) {
  if (toExecute->functionKeyName.equals("A")) FA();
  else if (toExecute->functionKeyName.equals("B"))
    FB();
  else if (toExecute->functionKeyName.equals("C"))
    FC();
  else if (toExecute->functionKeyName.equals("D"))
    FD();
}








#endif