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
  claw.open();
  delay(1500);
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
}

void robot::backward(int driveSpeed) {
  leftMotor.backward(driveSpeed);
  rightMotor.backward(driveSpeed);
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
    forward(lineSpeed);
    ReadIR();

  } else if (leftS == 0 && centerS == 0 && rightS == 0) {
    stop();
    ReadIR();

  }

}


void robot::grabCup() {
  centimeters = distanceSensor.measureDistanceCm();
  // Serial.println(centimeters);
  if (centimeters > 5) {
    claw.open();
   
  } else if (centimeters < 5) {
    delay(1000);
    claw.close();
    delay(1000);
    goBack();

  }
}

void robot::goBack() {
  turnRight();

}

void robot::CheckForCup() {
  centimeters = distanceSensor.measureDistanceCm();
  // Serial.println(centimeters);
  if (centimeters > 20) {
    forward(lineSpeed);
    grabCup();

  } else if (centimeters < 20) {
    turnRight();

  }
}


void robot::followLineIT() {
  //count = 0;
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
    turnRight();
    //count++;
    
  } else if (leftS == 0 && centerS == 0 && rightS == 0) {
    stop();

  }

}

