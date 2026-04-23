

#include <AStar32U4.h>

AStar32U4LCD lcd;

void setup()
{

}

void loop()
{
  bool usbPower = usbPowerPresent();

 

  // A-Star 32U4 Prime LV (ac03e)
  uint16_t batteryLevel = readBatteryMillivoltsLV4();



  // Print the results to the LCD.
  lcd.clear();
  lcd.print(F("B="));
  lcd.print(batteryLevel);
  lcd.print(F("mV"));
  lcd.gotoXY(0, 1);
  lcd.print(F("USB="));
  lcd.print(usbPower ? 'Y' : 'N');

  // Print the results to the serial monitor.
  Serial.print(F("USB="));
  Serial.print(usbPower ? 'Y' : 'N');
  Serial.print(F(" B="));
  Serial.print(batteryLevel);
  Serial.println(F(" mV"));

  delay(200);
}