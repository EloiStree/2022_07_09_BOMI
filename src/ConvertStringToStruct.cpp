#ifndef ConvertStringToStruct_CPP
#define ConvertStringToStruct_CPP

#include "Arduino.h"
#include "String.h"
#include "ExecuteStruct.h"
#include "StructUtility.h"
#include "StructUtility.cpp"
#include "LogStruct.cpp"
#include "SerialLog.cpp"
#include "ConvertStringToStruct.h"



// KeyboardExecutor* executor = new KeyboardExecutor();
// PressionRequest* pressRequest = new PressionRequest();
// CommandLineKeyValue* cmd = new CommandLineKeyValue();
// MidiAction* midiAction = new MidiAction();
// TransitToAllSerialText* transitionToAll = new TransitToAllSerialText();




static KeyboardExecutor* executor = new KeyboardExecutor();
static PressionRequest* pressRequesRequest = new PressionRequest();
static CommandLineKeyValue* cmd = new CommandLineKeyValue();
static MidiAction* midiRequest = new MidiAction();
static KeyboardFunctionStroke* keyboardfunctionRequest = new KeyboardFunctionStroke();
static KeyboardNumpadStroke* numpadRequest = new KeyboardNumpadStroke();
static KeyboardAlphaStroke* alphaRequest = new KeyboardAlphaStroke();
static TransitToAllSerialText* transitionToAllRequest = new TransitToAllSerialText();
static PrintDefaultSerialText* serialPrintRequest = new PrintDefaultSerialText();
static CallFunctionInArduino* callFunctionRequest = new CallFunctionInArduino();
static SwitchPinAsStringMode* pinStringRequest= new SwitchPinAsStringMode();
static KeyboardStringPrintAction* writeTextRequest = new KeyboardStringPrintAction();
static KeyboardCharTryToStrokeAction* charStrokeRequest =new KeyboardCharTryToStrokeAction();
static KeyboardControlString*  writeControlTextRequest=new KeyboardControlString();
static KeyboardStringPrintAction*  writeStringTextRequest=new KeyboardStringPrintAction();



static const void TryConvertAndExecute(String line){
	

 bool wasConverted=false;
 bool * converted = &wasConverted;
 cmd->Flush();
 ConvertToCommandLine(line, cmd );
 Log_Command(cmd);

if( TryConvertToText(cmd,   writeStringTextRequest ) ){
    LogPrintLn(">>T");
    Serial.print(">>T");
    Serial.println(writeStringTextRequest->toWrite);
    executor->Execute( writeStringTextRequest);
}
else if( TryConvertToMidi(cmd, pressRequesRequest ,  midiRequest ) ){
  LogPrintLn(">>0");
  Serial.println(">>0");
  Serial.println(midiRequest->note);
  Serial.println(" > ");
  Serial.println(midiRequest->velocity);
  Serial.println(" > ");
  Serial.println(midiRequest->channel);
  Serial.println(" > ");
    executor->Execute(pressRequesRequest, midiRequest);
}
else if(TryConvertTo(cmd,  transitionToAllRequest)){
  LogPrintLn(">>1");
    executor->Execute(transitionToAllRequest);
}else if(TryConvertTo(cmd,  keyboardfunctionRequest)){
  LogPrintLn(">>2");
    executor->Execute(pressRequesRequest,keyboardfunctionRequest);
}
else if(TryConvertTo(cmd,  numpadRequest)){
  LogPrintLn(">>3");
    executor->Execute(pressRequesRequest,numpadRequest);
}else if(TryConvertTo(cmd,  alphaRequest)){
  LogPrintLn(">>4");
    executor->Execute(pressRequesRequest,alphaRequest);
}
else if (TryConvertTo(cmd,  serialPrintRequest) ){
  LogPrintLn(">>5");
    executor->Execute(serialPrintRequest);
}
else if (TryConvertTo(cmd,  callFunctionRequest)) {
  LogPrintLn(">>6");
    executor->Execute(callFunctionRequest);
}
else if (TryConvertTo(cmd,  pressRequesRequest , pinStringRequest)) {
  LogPrintLn(">>7");
    executor->Execute(pressRequesRequest,pinStringRequest);
}
else if (TryConvertToControl(cmd,  pressRequesRequest , writeControlTextRequest)) {
  LogPrintLn(">>8");
    executor->Execute(pressRequesRequest,writeControlTextRequest);
}
else if (TryConvertTo(cmd,  pressRequesRequest , charStrokeRequest)) {
  
    LogPrintLn(">>9");
    executor->Execute(pressRequesRequest,charStrokeRequest);
}
else if (TryConvertTo(cmd,   writeTextRequest)) {
    LogPrintLn(">>10");
    executor->Execute(writeTextRequest);
}
//TryConvertTo(CommandLineKeyValue* cmd,  KeyboardStringPrintAction* actionOut)

//   line.trim();
//   LogPrint("Found Line:");
//   LogPrintLn(line);
//   int lineLenght = line.length();
//   if (lineLenght > 2 && line[0] == 'N' && line[1] == 'P') {
//     LogPrint("Keyboard Numpad parse:");
//     LogPrintLn(line);
//     //blePush.PushNumpad(line);
//   }  
//   else if (lineLenght > 1 && line[0] == 'K') {
//     LogPrint("Keyboard parse:");
//     LogPrintLn(line);
//     //blePush.PushKey(0x80, true, true);

//   } 
//   else if (lineLenght > 1 && line[0] == 'M') {
//     LogPrint("Midi parse:");
//     LogPrintLn(line);
//     TryConvertToMidi(converted, cmd, pressRequest, midiAction) ;
//     if(*converted)
//       Log(pressRequest, midiAction);
//     else 
//       LogPrintLn("Fail to convert Midi");
//     //blePush.PushMidi(50,127,5);

//   }  else if (lineLenght > 1 && line[0] == 'T') {

//     TryConvertTo(converted, cmd,  transitionToAll);
//     if(*converted)
//       Log(transitionToAll);
//     else 
//       LogPrintLn("Fail to convert  Transit All");
//   }  else if (lineLenght > 1 && line[0] == 'S') {

//       LogPrintLn("Fail to convert  Transit All");
//   }else if (lineLenght > 1 && line[0] == 'P') {

//     LogPrintLn(cmd->value);
//     // TryConvertToPinAction(converted, cmd,  );
//     // if(*converted)
//     //   Log(transitionToAll);
//     // else 
//     //   LogPrintLn("Fail to convert  Transit All");
//   }
//   else {
//     LogPrint("Unmanaged line:");
//     LogPrintLn(line);
//   }
	
	
	
	
}


#endif
