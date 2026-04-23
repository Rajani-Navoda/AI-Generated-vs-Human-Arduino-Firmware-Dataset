#include <Wire.h>
#include <LiquidCrystal_I2C.h>

// Motor control pins
#define MOTOR_LEFT_PWM 3
#define MOTOR_RIGHT_PWM 5
#define MOTOR_LEFT_DIR 2
#define MOTOR_RIGHT_DIR 4

// Joystick pins
#define JOY_X A0
#define JOY_Y A1
#define JOY_BTN 7

// LCD setup (set I2C address to 0x27, 16 chars, 2 lines)
LiquidCrystal_I2C lcd(0x27, 16, 2);

// Joystick thresholds
int joyX = 0;
int joyY = 0;
int joyButton = 0;
int motorSpeedLeft = 0;
int motorSpeedRight = 0;
int maxSpeed = 255;  // Max PWM value for motor

void setup() {
  // Initialize LCD
  lcd.begin();
  lcd.backlight();
  lcd.clear();
  
  // Initialize motor control pins
  pinMode(MOTOR_LEFT_PWM, OUTPUT);
  pinMode(MOTOR_RIGHT_PWM, OUTPUT);
  pinMode(MOTOR_LEFT_DIR, OUTPUT);
  pinMode(MOTOR_RIGHT_DIR, OUTPUT);
  
  // Initialize joystick button
  pinMode(JOY_BTN, INPUT_PULLUP);

  // Show startup message on LCD
  lcd.setCursor(0, 0);
  lcd.print("SmartCar Test");
  delay(2000);
  lcd.clear();
  
  Serial.begin(57600);
}

void loop() {
  // Read joystick values
  joyX = analogRead(JOY_X);
  joyY = analogRead(JOY_Y);
  joyButton = digitalRead(JOY_BTN);
  
  // Map joystick values to motor speeds
  motorSpeedLeft = map(joyY, 0, 1023, -maxSpeed, maxSpeed);
  motorSpeedRight = map(joyY, 0, 1023, -maxSpeed, maxSpeed);
  
  int turn = map(joyX, 0, 1023, -maxSpeed, maxSpeed);
  
  // Adjust motor speeds based on turning direction
  motorSpeedLeft -= turn;
  motorSpeedRight += turn;
  
  // Limit speed to avoid overflow
  motorSpeedLeft = constrain(motorSpeedLeft, -maxSpeed, maxSpeed);
  motorSpeedRight = constrain(motorSpeedRight, -maxSpeed, maxSpeed);
  
  // Set motor speeds
  setMotorSpeed(motorSpeedLeft, motorSpeedRight);
  
  // Display joystick status and motor speeds on LCD
  lcd.setCursor(0, 0);
  lcd.print("X: ");
  lcd.print(joyX);
  lcd.setCursor(8, 0);
  lcd.print("Y: ");
  lcd.print(joyY);
  
  lcd.setCursor(0, 1);
  lcd.print("L: ");
  lcd.print(motorSpeedLeft);
  lcd.setCursor(8, 1);
  lcd.print("R: ");
  lcd.print(motorSpeedRight);

  delay(100);  // Slow down updates for readability
}

// Motor control function
void setMotorSpeed(int leftSpeed, int rightSpeed) {
  analogWrite(MOTOR_LEFT_PWM, abs(leftSpeed));
  digitalWrite(MOTOR_LEFT_DIR, leftSpeed >= 0 ? HIGH : LOW);
  analogWrite(MOTOR_RIGHT_PWM, abs(rightSpeed));
  digitalWrite(MOTOR_RIGHT_DIR, rightSpeed >= 0 ? HIGH : LOW);
}
