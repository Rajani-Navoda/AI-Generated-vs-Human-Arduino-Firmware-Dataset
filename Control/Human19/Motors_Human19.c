

#include <AStar32U4.h>

AStar32U4Motors motors;

void setup()
{

}

void loop()
{
  // Run motor 1 forward.
  ledYellow(1);
  for (int speed = 0; speed <= 400; speed++)
  {
    motors.setM1Speed(speed);
    delay(2);
  }
  for (int speed = 400; speed >= 0; speed--)
  {
    motors.setM1Speed(speed);
    delay(2);
  }

  // Run motor 1 backward.
  ledYellow(0);
  for (int speed = 0; speed >= -400; speed--)
  {
    motors.setM1Speed(speed);
    delay(2);
  }
  for (int speed = -400; speed <= 0; speed++)
  {
    motors.setM1Speed(speed);
    delay(2);
  }

  // Run motor 2 forward.
  ledYellow(1);
  for (int speed = 0; speed <= 400; speed++)
  {
    motors.setM2Speed(speed);
    delay(2);
  }
  for (int speed = 400; speed >= 0; speed--)
  {
    motors.setM2Speed(speed);
    delay(2);
  }

  // Run motor 2 backward.
  ledYellow(0);
  for (int speed = 0; speed >= -400; speed--)
  {
    motors.setM2Speed(speed);
    delay(2);
  }
  for (int speed = -400; speed <= 0; speed++)
  {
    motors.setM2Speed(speed);
    delay(2);
  }

  delay(500);
}