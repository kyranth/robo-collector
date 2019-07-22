#include "robot.h"
#include "motor.h"
#include "sensor.h"
#include <Arduino.h>


// Configuration

int leftS = 1;
int centerS = 1;
int rightS = 1;

motor leftMotor(10, 9); // CW, CCW
motor rightMotor(6, 5);

sensor leftIR(A0);
sensor centerIR(A1);
sensor rightIR(A2);

robot::robot(){

}

void robot::begin(){
	Serial.begin(9600);
	Serial.println("Robot Ready");
}

void robot::ReadIR() {
  leftS = leftIR.DRead();
  centerS = centerIR.DRead();
  rightS = rightIR.DRead();
}

void robot::forward(int driveSpeed) {
  leftMotor.forward(driveSpeed);
  rightMotor.forward(driveSpeed);
  // Serial.println("---forward executed---");
  // delay(10);
}

void robot::backward(int driveSpeed) {
  leftMotor.backward(driveSpeed);
  rightMotor.backward(driveSpeed);
  // Serial.println("---backward executed---");
  // delay(10);
}

void robot::turnRight() {
  leftMotor.forward(200);
  rightMotor.backward(200);
}

void robot::turnLeft() {
  leftMotor.backward(200);
  rightMotor.forward(200);
}

void robot::stop() {
  leftMotor.stop();
  rightMotor.stop();
}

void robot::followLine() {
  int lineSpeed = 80;
  ReadIR();
  
  if(leftS == 0 && centerS == 1 && rightS == 0) {
    forward(lineSpeed);
    ReadIR();

  } else if (leftS == 0 && centerS == 1 && rightS == 1) {
    turnRight();
    ReadIR();

  } else if (leftS == 1 && centerS == 1 && rightS == 0) {
    turnLeft();
    ReadIR();

  } else if (leftS == 0 && centerS == 0 && rightS == 1) {
    // setColor(0, 0, 200);
    turnRight();
    ReadIR();

  } else if (leftS == 1 && centerS == 0 && rightS == 0) {
    // setColor(200, 0, 0);
    turnLeft();
    ReadIR();

  } else if (leftS == 1 && centerS == 1 && rightS == 1) {
    forward(lineSpeed);
    ReadIR();

  } else if (leftS == 0 && centerS == 0 && rightS == 0) {
    // setColor(200, 200, 200);
    leftMotor.stop();
    rightMotor.stop();
    ReadIR();

  }

}

void robot::CheckForCup() {
  
}

void robot::followLineIT() {
  int lineSpeed = 80;
  count = 0;
  ReadIR();
  if(leftS == 0 && centerS == 1 && rightS == 0) {
    forward(lineSpeed);
    ReadIR();

  } else if (leftS == 0 && centerS == 1 && rightS == 1) {
    turnRight();
    ReadIR();

  } else if (leftS == 1 && centerS == 1 && rightS == 0) {
    turnLeft();
    ReadIR();

  } else if (leftS == 0 && centerS == 0 && rightS == 1) {
    // setColor(0, 0, 200);
    turnRight();
    ReadIR();

  } else if (leftS == 1 && centerS == 0 && rightS == 0) {
    // setColor(200, 0, 0);
    turnLeft();
    ReadIR();

  } else if (leftS == 1 && centerS == 1 && rightS == 1) {
    leftMotor.stop();
    rightMotor.stop();
    ReadIR();
    count++;

  } else if (leftS == 0 && centerS == 0 && rightS == 0) {
    // setColor(200, 200, 200);
    leftMotor.stop();
    rightMotor.stop();
    ReadIR();
  } 

}

