#include "ALog.h"

ALog alog;

char* dataLoggerName = "SC 01";
char* fileName = "SC01.txt";

int Log_Interval_Seconds = 0;
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


 

  alog.startAnalog(); 

  delay(5); 


  alog.Honeywell_HSC_analog(1, 3.3, 3.3, 0, 30, 1, 6);

  alog.endAnalog(); 
  alog.endLogging();

}