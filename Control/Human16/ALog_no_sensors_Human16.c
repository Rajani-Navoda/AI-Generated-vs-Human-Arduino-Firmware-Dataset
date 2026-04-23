#include "ALog.h"

ALog alog;

char* dataLoggerName = "T01";
char* fileName = "T01.txt";

int Log_Interval_Seconds = 10; 
int Log_Interval_Minutes = 0; 
int Log_Interval_Hours = 0; 
bool external_interrupt = false;


void setup(){
  alog.initialize(dataLoggerName, fileName,
    Log_Interval_Hours, Log_Interval_Minutes, Log_Interval_Seconds, 
    external_interrupt);
  alog.setupLogger();
}

void loop(){
 
  alog.goToSleep_if_needed(); 
  alog.startLogging(); 
                         
 
  alog.endLogging();


}