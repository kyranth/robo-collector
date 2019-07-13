
#include <IRremote.h>
#include "motor.h"
#include "sensor.h"

const byte RECV_PIN = 4;
IRrecv irrecv(RECV_PIN);
decode_results results;
unsigned long key_value = 0;

motor leftMotor(10, 9); // CW, CCW
motor rightMotor(6, 5);

void robotForward(int driveSpeed, int driveTime) {
  leftMotor.forward(driveSpeed);
  rightMotor.backward(driveSpeed);
  delay(driveTime);
}

void robotBackward(int driveSpeed, int driveTime) {
  leftMotor.backward(driveSpeed);
  rightMotor.forward(driveSpeed);
  delay(driveTime);
}

void turnLeft(int turnAngle) {
  leftMotor.forward(240);
  rightMotor.forward(240);
  delay(turnAngle);

}

void turnRight(int turnAngle) {
  leftMotor.backward(240);
  rightMotor.backward(240);
  delay(turnAngle);

}

void setup () {
  Serial.begin(9600);

}

void loop() {
  robotForward(255, 1000);


}

//forward
//5 and 10
//backward
//6 and 9
