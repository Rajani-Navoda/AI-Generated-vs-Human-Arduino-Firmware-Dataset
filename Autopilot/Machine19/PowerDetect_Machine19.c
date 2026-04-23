#include <AStar32U4.h>
#include <AStar32U4LCD.h> // Include the LCD library

AStar32U4LCD lcd; // Create an instance of the A-Star 32U4 LCD

void setup() {
  // Initialize the LCD
  lcd.begin();

  // Start serial communication
  Serial.begin(9600);
}

void loop() {
  // Read the voltage on the VIN pin
  float vinVoltage = analogRead(A1) * (5.0 / 1023.0) * (10000.0 / (10000.0 + 1000.0)); // Adjust the resistor values as needed
  
  // Check if USB power is present
  bool usbPower = (digitalRead(USB_POWER_PIN) == HIGH); // Use the appropriate pin for USB detection

  // Print results to the LCD
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("VIN: ");
  lcd.print(vinVoltage);
  lcd.print(" V");
  
  lcd.setCursor(0, 1);
  lcd.print("USB: ");
  lcd.print(usbPower ? "Present" : "Absent");
  
  // Print results to the Serial Monitor
  Serial.print("VIN Voltage: ");
  Serial.print(vinVoltage);
  Serial.println(" V");
  
  Serial.print("USB Power: ");
  Serial.println(usbPower ? "Present" : "Absent");

  // Delay before the next reading
  delay(2000); // Adjust as necessary
}