#include <Wire.h>    // Include Wire library for I2C communication
#include <aE2.h>     // Include aE2 EEPROM library (if needed for EEPROM data logging)

aE2 eeprom;          // Create an instance of the aE2 EEPROM object (if needed for EEPROM)

// Variables for logging
unsigned long startTime;
unsigned long logInterval = 1000;  // Log every second
int logCount = 0;

void setup() {
  // Initialize Serial at 38400 bps
  Serial.begin(38400);    // Set baud rate to 38400 bps
  while (!Serial) {
    // Wait for the Serial port to initialize (especially important for some boards like Leonardo)
  }

  // Initialize any necessary peripherals (like EEPROM or SD card, if used)
  Wire.begin();
  eeprom.begin(); // Initialize EEPROM, if needed

  // Start the timer for logging
  startTime = millis();

  Serial.println("ALog_no_sensors Demo - Logging data every second.");
}

void loop() {
  unsigned long currentTime = millis();

  // Check if it's time to log data
  if (currentTime - startTime >= logInterval) {
    logData();         // Log the data
    startTime = currentTime;  // Reset timer for next log
  }

  // Add any other tasks in the main loop if needed
}

// Function to log data to Serial (and potentially to EEPROM or SD card)
void logData() {
  logCount++;

  // Log the timestamp and log count to the Serial Monitor
  Serial.print("Log Entry #");
  Serial.print(logCount);
  Serial.print(", Time: ");
  Serial.print(millis());
  Serial.println(" ms");

  // You can also log data to EEPROM or an SD card here, if needed:
  // e.g., eeprom.write... or SD.write...

  // Optional: log other variables like sensor readings, etc. (even if no sensors are used in this example)
  // Example: Log random data
  float randomData = random(0, 100) / 1.0;
  Serial.print("Random Data: ");
  Serial.println(randomData);
}
