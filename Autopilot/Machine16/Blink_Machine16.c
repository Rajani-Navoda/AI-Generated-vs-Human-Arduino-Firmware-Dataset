#include <Wire.h>    // Include Wire library for I2C communication (if needed for peripherals)
#include <aE2.h>     // Include aE2 EEPROM library (if needed for EEPROM storage)
#include <SD.h>      // Include the SD library (if using an SD card for logging)

#define LED_PIN 13   // Pin number for the LED (on most Arduinos, the built-in LED is on pin 13)
#define LOG_INTERVAL 1000  // Blink and log interval (1 second)
#define SD_CS_PIN 10       // SD card Chip Select pin (if SD card is used)

unsigned long startTime;
bool ledState = false;  // Variable to track the LED state
File logFile;           // File object for SD card logging (if used)

void setup() {
  // Set the LED pin as an output
  pinMode(LED_PIN, OUTPUT);

  // Start Serial communication
  Serial.begin(9600);   // Set baud rate to 9600 for Serial communication
  while (!Serial) {
    // Wait for the Serial port to initialize (important for some boards like Leonardo)
  }

  // Initialize I2C communication and EEPROM (if needed)
  Wire.begin();
  aE2 eeprom;
  eeprom.begin();

  // Initialize the SD card
  if (!SD.begin(SD_CS_PIN)) {
    Serial.println("SD card initialization failed!");
  } else {
    Serial.println("SD card initialized.");
    logFile = SD.open("log.txt", FILE_WRITE);
    if (!logFile) {
      Serial.println("Error opening log file!");
    } else {
      logFile.println("ALog BottleLogger - Blink LED Logging.");
    }
  }

  // Start the timer for logging
  startTime = millis();

  Serial.println("ALog BottleLogger - Blink LED started.");
}

void loop() {
  unsigned long currentTime = millis();

  // Check if it's time to toggle the LED and log the state
  if (currentTime - startTime >= LOG_INTERVAL) {
    toggleLED();         // Toggle the LED state
    logLEDState();       // Log the LED state
    startTime = currentTime;  // Reset the timer for the next blink/log
  }
}

// Function to toggle the LED on/off
void toggleLED() {
  ledState = !ledState;        // Toggle the LED state
  digitalWrite(LED_PIN, ledState);  // Set the LED to the new state
}

// Function to log the LED state to Serial, SD card, and optionally EEPROM
void logLEDState() {
  // Log the LED state to the Serial Monitor
  Serial.print("LED is ");
  Serial.println(ledState ? "ON" : "OFF");

  // Log to SD card (if the file is open)
  if (logFile) {
    logFile.print("LED is ");
    logFile.println(ledState ? "ON" : "OFF");
    logFile.flush();  // Ensure data is written to the SD card
  } else {
    Serial.println("Error writing to log file!");
  }

  // Optional: Log to EEPROM (if needed, using the aE2 library)
  // Example: log the LED state or blink count to EEPROM
  // e.g., eeprom.write... (if necessary for logging to EEPROM)
}
