#include "motor.h"
#include "Arduino.h"

motor::motor(int CW, int CCW)
{
  _CW = CW;
  _CCW = CCW;
  pinMode(CW, OUTPUT);
  pinMode(CCW, OUTPUT);
}

void motor::backward(int driveSpeed)
{
  analogWrite(_CW, LOW);
  analogWrite(_CCW, driveSpeed);
  //Debugging Purposes - DO NOT DELETE SERIAL.PRINTLN
  //Serial.println("---backward executed---");
  //delay(10);
}

void motor::forward(int driveSpeed)
{
  analogWrite(_CW, driveSpeed);
  analogWrite(_CCW, LOW);
  //Debugging Purposes - DO NOT DELETE SERIAL.PRINTLN
  //Serial.println("---forward executed---");
  //delay(10);
}

void motor::open()
{
  digitalWrite(_CW, LOW);
  digitalWrite(_CCW, HIGH);
}

void motor::close()
{
  digitalWrite(_CW, HIGH);
  digitalWrite(_CCW, LOW);
}

void motor::stop()
{
  digitalWrite(_CW, LOW);
  digitalWrite(_CCW, LOW);
  //Debugging Purposes - DO NOT DELETE SERIAL.PRINTLN
  //Serial.println("---stopped---");
  //delay(10);
}
