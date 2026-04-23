#include "ALog.h"

ALog alog;

char* dataLoggerName = "T01";
char* fileName = "T01.txt"; 


int Log_Interval_Seconds = 0; 
int Log_Interval_Minutes = 0; 
int Log_Interval_Hours = 0; 
int Log_Interval_Days = 0; 

bool external_interrupt = false;

void setup(){
  delay(50);
  pinMode(3, INPUT); 
  digitalWrite(3, HIGH);
  alog.initialize(dataLoggerName, fileName, Log_Interval_Days, \
      Log_Interval_Hours, Log_Interval_Minutes, Log_Interval_Seconds,
      external_interrupt);alog.setupLogger();
  pinMode(3, INPUT); 
  digitalWrite(3, HIGH);
  delay(100);
  interrupts();

alog.startAnalog();
}

void loop(){

if (alog.get_use_sleep_mode() == true){
  alog.sleep();
}
alog.startLogging(); 

alog.Barometer_BMP180();


alog.thermistorB(10000, 3950, 10000, 25, A0); 


alog.maxbotixHRXL_WR_analog(5,A1,99,0);

alog.readPin(A2);

alog.Honeywell_HSC_analog(A7,5.0,3.3,0.0,30.0,1,6);


alog.endLogging();

}