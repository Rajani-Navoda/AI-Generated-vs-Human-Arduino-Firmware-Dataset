#include <Wire.h>    // Include Wire library for I2C communication
#include <aE2.h>     // Include the aE2 EEPROM library

aE2 eeprom;  // Create an instance of the aE2 EEPROM object

// Variables to store data
float humidity;
float temperature;
unsigned char state;
String description;

void setup() {
  Serial.begin(9600);    // Start serial communication
  Wire.begin();          // Initialize I2C communication
  eeprom.begin();        // Initialize the EEPROM

  Serial.println("AGU 2016 Demo - Enter values for EEPROM storage.");

  // Prompt the user for input
  getUserInput();

  // Write user input to EEPROM
  writeDataToEEPROM();

  // Read data from EEPROM and print it
  readDataFromEEPROM();
}

void loop() {
  // Do nothing here
}

// Function to get user input from the Serial Monitor
void getUserInput() {
  Serial.println("Enter humidity value (float): ");
  while (Serial.available() == 0) {}  // Wait for input
  humidity = Serial.parseFloat();     // Read humidity as a float
  Serial.print("Humidity entered: ");
  Serial.println(humidity);

  Serial.println("Enter temperature value (float): ");
  while (Serial.available() == 0) {}  // Wait for input
  temperature = Serial.parseFloat();  // Read temperature as a float
  Serial.print("Temperature entered: ");
  Serial.println(temperature);

  Serial.println("Enter state (0 or 1): ");
  while (Serial.available() == 0) {}  // Wait for input
  state = Serial.parseInt();          // Read state as an unsigned char (int will work for 0 or 1)
  Serial.print("State entered: ");
  Serial.println(state);

  Serial.println("Enter a description: ");
  while (Serial.available() == 0) {}  // Wait for input
  description = Serial.readString();  // Read the description as a string
  Serial.print("Description entered: ");
  Serial.println(description);
}

// Function to write the variables to EEPROM
void writeDataToEEPROM() {
  int addr = 0; // Start at address 0

  // Write humidity (4 bytes)
  eeprom.writeFloat(addr, humidity);
  addr += sizeof(float);

  // Write temperature (4 bytes)
  eeprom.writeFloat(addr, temperature);
  addr += sizeof(float);

  // Write state (1 byte)
  eeprom.writeByte(addr, state);
  addr += sizeof(unsigned char);

  // Write description (length + characters)
  int len = description.length();
  eeprom.writeByte(addr, len); // Write the length of the string
  addr += sizeof(byte);
  for (int i = 0; i < len; i++) {
    eeprom.writeByte(addr + i, description[i]); // Write each character of the string
  }
  addr += len;

  Serial.println("Data written to EEPROM.");
}

// Function to read the variables from EEPROM
void readDataFromEEPROM() {
  int addr = 0; // Start at address 0

  // Read humidity
  humidity = eeprom.readFloat(addr);
  addr += sizeof(float);

  // Read temperature
  temperature = eeprom.readFloat(addr);
  addr += sizeof(float);

  // Read state
  state = eeprom.readByte(addr);
  addr += sizeof(unsigned char);

  // Read description
  byte len = eeprom.readByte(addr); // Read the length of the string
  addr += sizeof(byte);
  description = "";
  for (int i = 0; i < len; i++) {
    description += (char)eeprom.readByte(addr + i); // Read each character
  }
  addr += len;

  // Print the read data
  Serial.println("Reading from EEPROM...");
  Serial.print("Humidity: ");
  Serial.println(humidity);
  Serial.print("Temperature: ");
  Serial.println(temperature);
  Serial.print("State: ");
  Serial.println(state);
  Serial.print("Description: ");
  Serial.println(description);
}
