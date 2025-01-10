/**
 * @file motor.cpp
 * @brief Implementation of the motor
 * @author kyranth
 * @date 2019-07-26
 *
 * This file contains the implementation of the motor.
 */

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
  //Serial.println("---backward executed---");
  //delay(10);
}

void motor::forward(int driveSpeed)
{
  analogWrite(_CW, driveSpeed);
  analogWrite(_CCW, LOW);
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
  //Serial.println("---stopped---");
  //delay(10);
}
