#include "motor.h"
#include "Arduino.h"

motor::motor(int _CW, int _CCW) {
  // _CW - inuput = defined variable
  _CW = CW;
  _CCW = CCW;
  pinMode(CW, OUTPUT);
  pinMode(CCW, OUTPUT);
}

void motor::backward(int driveSpeed) {
  analogWrite(CW, LOW);
  analogWrite(CCW, driveSpeed);
  //Debugging Purposes - DO NOT DELETE SERIAL.PRINTLN
  //Serial.println("---backward executed---");
  //delay(10);
}

void motor::forward(int driveSpeed) {
  analogWrite(CW, driveSpeed);
  analogWrite(CCW, LOW);
  //Debugging Purposes - DO NOT DELETE SERIAL.PRINTLN
  //Serial.println("---forward executed---");
  //delay(10);
}

void motor::stop() {
  analogWrite(CW, LOW);
  analogWrite(CCW, LOW);
  //Debugging Purposes - DO NOT DELETE SERIAL.PRINTLN
  //Serial.println("---stopped---");
  //delay(10);
}
