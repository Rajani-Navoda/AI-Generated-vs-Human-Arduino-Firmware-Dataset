#include <Wire.h>    // Include Wire library for I2C communication
#include <aE2.h>     // Include aE2 EEPROM library (if necessary for EEPROM storage)
#include <SD.h>      // Include the SD library (if using an SD card for logging)

#define LOG_INTERVAL 1000  // Log every second
#define SD_CS_PIN 10       // Pin for SD card Chip Select (CS)

unsigned long startTime;
int logCount = 0;

File logFile;  // File object for writing to SD card (if used)

void setup() {
  // Start Serial communication
  Serial.begin(9600);  // Set baud rate to 9600 for general Serial Monitor use
  while (!Serial) {
    // Wait for Serial to initialize (important for some boards like Leonardo)
  }

  // Initialize I2C communication and EEPROM (if used)
  Wire.begin();
  aE2 eeprom;
  eeprom.begin();

  // Initialize the SD card
  if (!SD.begin(SD_CS_PIN)) {
    Serial.println("SD card initialization failed!");
    return;
  }
  Serial.println("SD card initialized.");

  // Create or open the log file
  logFile = SD.open("log.txt", FILE_WRITE);
  if (!logFile) {
    Serial.println("Error opening log file!");
  } else {
    logFile.println("ALog BasicStart - Logging initiated.");
  }

  // Start the timer for logging
  startTime = millis();

  Serial.println("ALog BasicStart - Logging started.");
}

void loop() {
  unsigned long currentTime = millis();

  // Check if it's time to log data
  if (currentTime - startTime >= LOG_INTERVAL) {
    logData();         // Log the data
    startTime = currentTime;  // Reset timer for the next log
  }

  // Add any other tasks you need in the main loop
}

// Function to log data to Serial, SD card, and EEPROM (if needed)
void logData() {
  logCount++;

  // Log the timestamp and log count to the Serial Monitor
  Serial.print("Log Entry #");
  Serial.print(logCount);
  Serial.print(", Time: ");
  Serial.print(millis());
  Serial.println(" ms");

  // Log data to SD card if the file is available
  if (logFile) {
    logFile.print("Log Entry #");
    logFile.print(logCount);
    logFile.print(", Time: ");
    logFile.print(millis());
    logFile.println(" ms");
    logFile.flush();  // Ensure data is written to the SD card
  } else {
    Serial.println("Error writing to log file!");
  }

  // Optional: Log data to EEPROM (if used)
  // For instance, you can log the logCount or timestamp to EEPROM.
  // e.g., eeprom.write... (using the aE2 library)

  // Optional: Log other variables, sensor data, etc.
  // Example: Log random data (for demo purposes)
  float randomData = random(0, 100) / 1.0;
  Serial.print("Random Data: ");
  Serial.println(randomData);
  if (logFile) {
    logFile.print("Random Data: ");
    logFile.println(randomData);
    logFile.flush();
  }
}
