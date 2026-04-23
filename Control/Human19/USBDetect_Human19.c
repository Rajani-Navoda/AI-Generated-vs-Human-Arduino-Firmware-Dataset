#include <AStar32U4.h>

AStar32U4LCD lcd;

void setup()
{

}

void loop()
{
 
  bool usbPower = usbPowerPresent();

 
  bool usbConfigured = USBDevice.configured();

  bool portOpen = Serial;

  // Turn on the yellow LED if USB power is present.
  ledYellow(usbPower);

  // Turn on the red LED if USB is configured.
  ledRed(usbConfigured);

  // Turn on the green TX LED if the serial port is open.
  ledGreen(portOpen);

  // Display the results on the LCD every 100 ms.
  static uint16_t lastDisplayTime = 0;
  if ((uint16_t)(millis() - lastDisplayTime) > 100)
  {
    lcd.clear();
    lcd.print(F("Pow="));
    lcd.print(usbPower ? 'Y' : 'N');
    lcd.gotoXY(0, 1);
    lcd.print(F("C="));
    lcd.print(usbConfigured ? 'Y' : 'N');
    lcd.print(F(" O="));
    lcd.print(portOpen ? 'Y' : 'N');
  }
}