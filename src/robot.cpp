#include "robot.h"
#include "motor.h"
#include "sensor.h"
#include <Arduino.h>
#include <HCSR04.h>

// Configuration
int leftS = 1;
int centerS = 1;
int rightS = 1;

int lineSpeed = 80;

motor leftMotor(10, 9); // CW, CCW
motor rightMotor(6, 5);
motor elbow(2, 4);
motor claw(7, 8);

sensor leftIR(A0);
sensor centerIR(A1);
sensor rightIR(A2);
UltraSonicDistanceSensor distanceSensor(A4, A3);

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

void robot::clawOpen() {
  claw.open();
} 

void robot::clawClose () {
  claw.close();
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


void robot::grabCup() {
  centimeters = distanceSensor.measureDistanceCm();
  forward(lineSpeed);
  if (centimeters > 5) {
    claw.open();

  } else if (centimeters < 5) {
    stop();
    delay(1000);
    claw.close();
    
  }
  
}

void robot::CheckForCup() {
  centimeters = distanceSensor.measureDistanceCm();
  if (centimeters > 15) {
    forward(lineSpeed);

  } else {
    goBack();

  }
}

void robot::goBack() {
  turnRight();
  forward(lineSpeed);
  followLineIT();

}

void robot::followLineIT() {
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
    turnRight();
    ReadIR();

  } else if (leftS == 1 && centerS == 0 && rightS == 0) {
    turnLeft();
    ReadIR();

  } else if (leftS == 1 && centerS == 1 && rightS == 1) {
    juncVar++;
    ReadIR();
    
  } else if (leftS == 0 && centerS == 0 && rightS == 0) {
    grabCup();
    ReadIR();
  } 

}

void robot::junction() {
  
  
}