#ifndef LOGSTRUCT_H
#define LOGSTRUCT_H
#include "Arduino.h"
#include "String.h"
#include "StructUtility.h"
#include "SerialLog.cpp"


static const void Log_Command(CommandLineKeyValue* command) {


  LogPrintLn();
  LogPrint("> Command Start:");
  LogPrint(command->rawOrigine);
  LogPrint("|");
  LogPrint(command->rawOrigineTrimmed);
  LogPrint("|");
  LogPrint(command->key);
  LogPrint("|");
  LogPrint(command->keyLength);
  LogPrint("|");
  LogPrint(command->value);
  LogPrint("|");
  LogPrint(command->valueLength);
  LogPrintLn("> Command End");
}


static const void Log( TransitToAllSerialText* transitAction ){

LogPrintLn("");
LogPrintLn("Log to transit:");
LogPrint(transitAction->textToPrint);
LogPrintLn("<>");
}


static const void Log(MidiAction* midi){

LogPrintLn("");
LogPrintLn("Log Midi:");
  LogPrint("|");
LogPrint(midi->note);
  LogPrint("|");
LogPrint(midi->velocity);
  LogPrint("|");
LogPrint(midi->channel);
LogPrintLn("<>");
}


static const void Log(PressionRequest* action ,MidiAction* midi){

LogPrintLn("");
LogPrintLn("Log Midi:");
  LogPrint("|");
LogPrint(midi->note);
  LogPrint("|");
LogPrint(midi->velocity);
  LogPrint("|");
LogPrint(midi->channel);
  LogPrint("|");
LogPrint(action->press);
  LogPrint("|");
LogPrint(action->release);
LogPrintLn("<>");
}

#endif