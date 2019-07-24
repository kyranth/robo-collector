#include "robot.h"
#include "motor.h"
#include "sensor.h"
#include <Arduino.h>
#include <HCSR04.h>

// Configuration
int leftS = 1;
int centerS = 1;
int rightS = 1;
bool isThereCup = false;

int lineSpeed = 160;

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
  claw.close();
  delay(500);
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

void robot::goBack() {
  ReadIR();
  while (centerS == 0) {
    turnRight();
    ReadIR();
  }

}

void robot::grabCup() {
  centimeters = distanceSensor.measureDistanceCm();
  Serial.println(centimeters);
  if (centimeters > 7) {
    claw.open();
    delay(1000);
    goBack();
   
  } else if (centimeters < 7 && centimeters > 0) {
     claw.close();
     delay(1000);
     isThereCup = true;
     goBack();

  } 
}

void robot::junction() {
  if (count == 1) {
    forward(lineSpeed);
    delay(200);   // 100
    stop();
    ReadIR();
    while (centerS == 1) {
      turnRight();
      ReadIR();

  } while (centerS == 0) {
      turnRight();
      ReadIR(); }

    goBack();

  } else if (count == 2) {
      forward(255);
      delay(200);   // 200
      ReadIR();

  } else if (count == 3) {
    forward(lineSpeed);
    delay(200);
    ReadIR();
    while (centerS == 1) {
      turnLeft();
      ReadIR();

  } while (centerS == 0) {
      turnLeft();
      ReadIR();
      count = 0;
  }

  }
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
    count++;
    junction();
    ReadIR();

  } else if (leftS == 0 && centerS == 0 && rightS == 0) {
    stop();
    delay(2000);
    grabCup();
    ReadIR();

  } 

}

