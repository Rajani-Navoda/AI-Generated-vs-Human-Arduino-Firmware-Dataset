#include <EEPROM.h>

// Define pins for motors, sonar, etc.
#define MOTOR_LEFT_PWM 3
#define MOTOR_RIGHT_PWM 5
#define MOTOR_LEFT_DIR 2
#define MOTOR_RIGHT_DIR 4
#define SONAR_TRIGGER_PIN 7
#define SONAR_ECHO_PIN 6

// PID Parameters
float kp = 1.0, ki = 0.0, kd = 0.0;
float lastError = 0, integral = 0;

// Sonar (Ping) Parameters
#define USE_SONAR true
#define SONAR_MAX_DISTANCE 200  // Maximum sonar distance in cm

// Unicycle model parameters
float velocity = 0;
float angularVelocity = 0;

// Serial communication
unsigned long lastCommandTime = 0;
const unsigned long commandTimeout = 5000;

void setup() {
  // Initialize serial communication
  Serial.begin(57600);
  while (!Serial) {
    ;  // Wait for serial port to connect
  }
  
  pinMode(MOTOR_LEFT_PWM, OUTPUT);
  pinMode(MOTOR_RIGHT_PWM, OUTPUT);
  pinMode(MOTOR_LEFT_DIR, OUTPUT);
  pinMode(MOTOR_RIGHT_DIR, OUTPUT);

  if (USE_SONAR) {
    pinMode(SONAR_TRIGGER_PIN, OUTPUT);
    pinMode(SONAR_ECHO_PIN, INPUT);
  }
  
  loadEEPROMParameters();
  
  Serial.println("MD_SmartCar Calibration Initialized.");
  Serial.println("Commands: ");
  Serial.println("  set_pid Kp Ki Kd");
  Serial.println("  set_unicycle V W");
  Serial.println("  save_eeprom");
  Serial.println("  read_sonar");
}

void loop() {
  if (Serial.available()) {
    String command = Serial.readStringUntil('\n');
    command.trim();
    processCommand(command);
    lastCommandTime = millis();
  }
  
  // Timeout reset
  if (millis() - lastCommandTime > commandTimeout) {
    stopMotors();
  }
}

// Process incoming serial commands
void processCommand(String command) {
  if (command.startsWith("set_pid")) {
    sscanf(command.c_str(), "set_pid %f %f %f", &kp, &ki, &kd);
    Serial.print("PID parameters set to: ");
    Serial.print(kp);
    Serial.print(", ");
    Serial.print(ki);
    Serial.print(", ");
    Serial.println(kd);
  }
  else if (command.startsWith("set_unicycle")) {
    sscanf(command.c_str(), "set_unicycle %f %f", &velocity, &angularVelocity);
    controlUnicycleModel(velocity, angularVelocity);
    Serial.print("Unicycle model set to V=");
    Serial.print(velocity);
    Serial.print(", W=");
    Serial.println(angularVelocity);
  }
  else if (command.startsWith("save_eeprom")) {
    saveEEPROMParameters();
    Serial.println("EEPROM parameters saved.");
  }
  else if (command.startsWith("read_sonar") && USE_SONAR) {
    float distance = readSonar();
    Serial.print("Sonar distance: ");
    Serial.print(distance);
    Serial.println(" cm");
  }
  else {
    Serial.println("Unknown command.");
  }
}

// Motor control functions
void setMotorSpeed(int leftSpeed, int rightSpeed) {
  analogWrite(MOTOR_LEFT_PWM, abs(leftSpeed));
  digitalWrite(MOTOR_LEFT_DIR, leftSpeed >= 0 ? HIGH : LOW);
  analogWrite(MOTOR_RIGHT_PWM, abs(rightSpeed));
  digitalWrite(MOTOR_RIGHT_DIR, rightSpeed >= 0 ? HIGH : LOW);
}

void stopMotors() {
  setMotorSpeed(0, 0);
}

// Unicycle control model
void controlUnicycleModel(float v, float w) {
  int leftSpeed = v - w;
  int rightSpeed = v + w;
  setMotorSpeed(leftSpeed, rightSpeed);
}

// PID control
float pidControl(float setPoint, float actualPosition) {
  float error = setPoint - actualPosition;
  integral += error;
  float derivative = error - lastError;
  lastError = error;
  
  return kp * error + ki * integral + kd * derivative;
}

// EEPROM save/load functions
void saveEEPROMParameters() {
  EEPROM.put(0, kp);
  EEPROM.put(sizeof(float), ki);
  EEPROM.put(2 * sizeof(float), kd);
}

void loadEEPROMParameters() {
  EEPROM.get(0, kp);
  EEPROM.get(sizeof(float), ki);
  EEPROM.get(2 * sizeof(float), kd);
}

// Sonar read function
float readSonar() {
  digitalWrite(SONAR_TRIGGER_PIN, LOW);
  delayMicroseconds(2);
  digitalWrite(SONAR_TRIGGER_PIN, HIGH);
  delayMicroseconds(10);
  digitalWrite(SONAR_TRIGGER_PIN, LOW);
  
  unsigned long duration = pulseIn(SONAR_ECHO_PIN, HIGH);
  float distance = duration * 0.034 / 2;
  
  return distance;
}
