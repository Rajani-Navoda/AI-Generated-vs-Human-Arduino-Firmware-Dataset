#include <Wire.h>

#define HSC_SENSOR_ADDRESS 0x28  // I2C address for Honeywell HSC sensors

void setup() {
  Wire.begin();        // Initialize I2C communication
  Serial.begin(9600);  // Initialize serial communication for debugging
}

void loop() {
  Wire.requestFrom(HSC_SENSOR_ADDRESS, 4); // Request 4 bytes from the sensor

  if (Wire.available() == 4) {
    byte msb = Wire.read();      // Most significant byte
    byte lsb = Wire.read();      // Least significant byte
    byte temp_msb = Wire.read(); // Temperature most significant byte
    byte temp_lsb = Wire.read(); // Temperature least significant byte

    int pressure_raw = (msb << 8) | lsb;
    int temperature_raw = (temp_msb << 8) | temp_lsb;

    float pressure = pressure_raw * 0.001;     // Convert to appropriate units
    float temperature = temperature_raw * 0.01; // Convert to degrees Celsius

    Serial.print("Pressure: ");
    Serial.print(pressure);
    Serial.print(" kPa, Temperature: ");
    Serial.print(temperature);
    Serial.println(" °C");
  } else {
    Serial.println("Error reading from sensor.");
  }

  delay(1000); // Wait before the next reading
}
