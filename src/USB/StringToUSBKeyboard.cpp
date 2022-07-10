#include "Arduino.h"
#include "StringToUSBKeyboard.h"
#include "Keyboard.h"
#include "SerialLog.cpp"

//#include "MouseAndKeyboard.h"

StringToUSBKeyboard::StringToUSBKeyboard() {}

void StringToUSBKeyboard::Init() {
  Keyboard.begin();
  Keyboard.releaseAll();
}
void StringToUSBKeyboard::SwitchLanguageOnWindow() {
  Keyboard.press(0x80);
  Keyboard.press(0x81);
  Keyboard.release(0x81);
  Keyboard.release(0x80);
}

void StringToUSBKeyboard::ConvertStringToNumpadKeys(String text) {

}


void StringToUSBKeyboard::TryToParseTextToUnicode(String commandline) {
  
}

void StringToUSBKeyboard::TryToParseTextToAction(String commandline) {

}



void StringToUSBKeyboard::Push(uint8_t key, bool press, bool release) {

  if (press)
    Keyboard.press(key);
  if (release)
    Keyboard.release(key);
}
void StringToUSBKeyboard::Push(char key, bool press, bool release) {

  if (press)
    Keyboard.press(key);
  if (release)
    Keyboard.release(key);
}
void StringToUSBKeyboard::PushWithDelayIfNeeded(uint8_t key, bool press, bool release, int delayMS) {

  if (press)
    Keyboard.press(key);
  if (press && release)
    delay(delayMS);
  if (release)
    Keyboard.release(key);
  Keyboard.flush();
}
void StringToUSBKeyboard::PushWithDelayIfNeeded(char key, bool press, bool release, int delayMS) {

  if (press)
    Keyboard.press(key);
  if (press && release)
    delay(delayMS);
  if (release)
    Keyboard.release(key);
  Keyboard.flush();
}

void StringToUSBKeyboard::PushLearningTest() {
}
void StringToUSBKeyboard::ReleaseAllKey() {

  Keyboard.releaseAll();
}














/*
Keyboard.write(65);         // sends ASCII value 65, or A
Keyboard.write('A');            // same thing as a quoted character
Keyboard.write(0x41);       // same thing in hexadecimal
Keyboard.write(0b01000001); // same thing in binary (weird choice, but it works)
*/

/**
//Source:https://forum.arduino.cc/t/keyboard-write-with-number-pad-keys-from-leonardo/175304/6
220 '\334' Keypad /
221 '\335' Keypad *
222 '\336' Keypad -
223 '\337' Keypad +
224 '\340' Keypad ENTER
225 '\341' Keypad 1 and End
226 '\342' Keypad 2 and Down Arrow
227 '\343' Keypad 3 and PageDn
228 '\344' Keypad 4 and Left Arrow
229 '\345' Keypad 5
230 '\346' Keypad 6 and Right Arrow
231 '\347' Keypad 7 and Home
232 '\350' Keypad 8 and Up Arrow
233 '\351' Keypad 9 and PageUp
234 '\352' Keypad 0 and Insert
235 '\353' Keypad . and Delete

*/


//If unrecognized or too long
//Push as a text
//A is 65, 97



// void WriteText(String text);
// void PressChar(char text);
// void ReleaseChar(char text);