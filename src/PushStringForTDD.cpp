
#include "ConvertStringToStruct.h"
#include "ConvertStringToStruct.cpp"
const bool useDelay=true;
const int timeBetweenDelayPush=300;

static const void PushLine(String line) {
 TryConvertAndExecute(line);
}

static const void PushLineWithDelay(String line){

  PushLine(line);
    if(useDelay)    
      delay(timeBetweenDelayPush);
}



static const void TDD_Workspace(){

// for (int i =0; i<4;i++){
  
//   PushLineWithDelay("PP:13"); // Put the pin 1 on Hight
//   PushLineWithDelay("PR:13"); // Put the pin 1 on Hight
//   PushLineWithDelay("PP:13"); // Put the pin 1 on Hight
//   PushLineWithDelay("PR:13"); // Put the pin 1 on Hight
  // PushLineWithDelay("T:Some Message:io:lk");
  // PushLineWithDelay("K:F12");
  // PushLineWithDelay("K:F1");
  // PushLineWithDelay("KP:F5");
  // PushLineWithDelay("KR:F2");
  // PushLineWithDelay("M:50");
  // PushLineWithDelay("M:50,100,3");
  // PushLineWithDelay("KP:A");
  // PushLineWithDelay("KR:A");
  // PushLineWithDelay("K:A7"); //Stroke 1 on alpha bar up the keyboard
  // PushLineWithDelay("K:NP9");// Stroke 1 on the numpad
  PushLineWithDelay("K:N6"); // stroke 1 on the numpad  crash to correct;
  PushLineWithDelay("K:F24"); // Stroke the F1 key
  PushLineWithDelay("KP:Ctrl"); // Stroke the ctrl key
  PushLineWithDelay("KR:Ctrl"); // Stroke the ctrl key
  PushLineWithDelay("K:Control"); // Stroke the Control key
  PushLineWithDelay("K:Left"); // Stroke the Control key
  PushLineWithDelay("K:Up"); // Stroke the Control key
  //PushLineWithDelay("S:Hello World!!!"); // Print Hello world on the arduino serial
  //PushLineWithDelay("PP:13"); // Put the pin 13 on High
  //PushLineWithDelay("PR:13"); // Put the pin 13 on Low
  //PushLineWithDelay("F:A"); // Call function A registered in Arduino if added
	PushLineWithDelay("K:Left"); // Stroke the Control key
  
}

static const void TryToMakeItCrash(){
  PushLineWithDelay("T:Some T: Message:io:lk");
  PushLineWithDelay("M:50:10:10:10");
  PushLineWithDelay("M:50,10,10,10");
  PushLineWithDelay("M:50,100,3");
}

static const void CouldBeCoolToHaveButHard(){
  // Press the key A depending of the layer given to arduino EN to BE-FR from example
  PushLineWithDelay("KLP:A");
  PushLineWithDelay("KLR:A");
  PushLineWithDelay("C:STOP"); // Try to push the command to release all keyboard, mouse or other on the arduino
  PushLineWithDelay("M:...-,A"); // Try to push the command to release all keyboard, mouse or other on the arduino
  
  PushLineWithDelay("KI:255"); // Request to just convert and push the id to the keyboard lib without translation
  PushLineWithDelay("KI:0xFF");
}
static const void TDD_TestAll(){
	TDD_Workspace();
	TryToMakeItCrash();
	CouldBeCoolToHaveButHard();
}