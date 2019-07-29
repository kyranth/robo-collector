#include "robot.h"
#include "motor.h"
#include "sensor.h"
#include <Arduino.h>
#include <HCSR04.h>

// Configuration
int leftS = 1, centerS = 1, rightS = 1;
int cupleftIR = 1, cuprightIR = 1;
int rightCup = 0, leftCup = 0;

int junctionNum = 0, houseNum = 0;
int cupColor = 0;

int lineSpeed = 200;

unsigned long time;

byte clawState;
byte cupState;
byte elbowState;

motor leftMotor(10, 9); // CW, CCW
motor rightMotor(6, 5);
motor elbow(2, 4);
motor claw(7, 8);

sensor leftIR(A0);
sensor centerIR(A1);
sensor rightIR(A2);
sensor cupSensorRight(11);
sensor cupSensorLeft(12);

UltraSonicDistanceSensor distanceSensor(A4, A3);

robot::robot(){
}

/*
  - Baud rate: 9600
  - open claw
  - close claw
   ---------------------------------------------------------------------------*/
void robot::begin(){
	Serial.begin(9600);
	Serial.println("Robot Ready");

  claw.close();
  delay(500);
  claw.open();
  delay(1500);
  claw.stop();
}

/*
  - open claw
  - clawState = 0
   ---------------------------------------------------------------------------*/
void robot::clawOpen() {
  claw.open();
  clawState = 0;
} 

/*
  - close claw
  - clawState = 0
   ---------------------------------------------------------------------------*/
void robot::clawClose () {
  claw.close();
  clawState = 1;
}

/*
  - left motor forward
  - right motor forward
   ---------------------------------------------------------------------------*/
void robot::forward(int driveSpeed) {
  leftMotor.forward(driveSpeed);
  rightMotor.forward(driveSpeed);
}

/*
  - left motor backward
  - right motor backward
   ---------------------------------------------------------------------------*/
void robot::backward(int driveSpeed) {
  leftMotor.backward(driveSpeed);
  rightMotor.backward(driveSpeed);
}

/*
  - left motor forward
  - right motor backward
   ---------------------------------------------------------------------------*/
void robot::turnRight() {
  leftMotor.forward(200);
  rightMotor.backward(200);
}

/*
  - left motor backward
  - right motor forward
   ---------------------------------------------------------------------------*/
void robot::turnLeft() {
  leftMotor.backward(200);
  rightMotor.forward(200);
}

/*
  - left motor stop
  - right motor stop
   ---------------------------------------------------------------------------*/
void robot::stop() {
  leftMotor.stop();
  rightMotor.stop();
}

//****************************************************************************************************************************************************

/*
  - stand
  - blocking function
   ---------------------------------------------------------------------------*/
void robot::ReadIR() {
  leftS = leftIR.DRead();
  centerS = centerIR.DRead();
  rightS = rightIR.DRead();
}

void robot::readCupIR() {
  rightCup = cupSensorRight.DRead();
  leftCup = cupSensorLeft.DRead();

  if (rightCup == 1 && leftCup == 1) { // Black = Plastic
    // go to platic
    cupColor = 1;
  }
  else if (leftCup == 0 && rightCup == 0) { // White = Paper
    // go to paper
    cupColor = 2;
  }
  else if ((leftCup == 1 && rightCup == 0) || (leftCup == 0 && rightCup == 1)){   // Black & White = Everything else
    // go to everything else
    cupColor = 3;
  } else {
    cupColor = 0;

  }
}

/*
  - Read ultrasonic sensor
   ---------------------------------------------------------------------------*/
void robot::ultrasonicRead() {
  centimeters = distanceSensor.measureDistanceCm();
  Serial.println(centimeters);
}

/*
  - stand
  - blocking function
   ---------------------------------------------------------------------------*/
void robot::grabCup() {
  ultrasonicRead();
  readCupIR();
  if (centimeters > 7) {
    claw.open();
    delay(1000);
    claw.stop();
    ultrasonicRead();
    readCupIR();

  } else if (centimeters < 7 && centimeters > 0) {
     switch (cupColor) {
      case 1:
        claw.close();
        delay(200);
        claw.stop();
        cupState = 1;
        readCupIR();
        ultrasonicRead();
        break;

      case 2:
        goBack();
        readCupIR();
        ultrasonicRead();
        break;

      case 3:
        goBack();
        readCupIR();
        ultrasonicRead();
        break;

      default:
        goBack();
        readCupIR();
        ultrasonicRead();
        break;
     }

  }
}

/*
  - Grab cup if within 7 cm
  - Lift cup upto the holder
   ---------------------------------------------------------------------------*/
void robot::grabnLiftCup() {
  grabCup();
  if (cupState == 1) {
    elbow.close();
    delay(1500);
    elbow.stop();
    clawOpen();
    delay(1000);
    elbow.open();
    delay(1500);
    elbow.stop();
    clawOpen();
    elbowState = 1;
    cupState = 0;
    readCupIR();

  } else {
    cupState = 0;
    readCupIR();
    ultrasonicRead();
    goBack();

  }
  
}

/*
  - Lift elbow until cm is not > 7
  - 
   ---------------------------------------------------------------------------*/
void robot::putBack() {
  elbow.close();
  delay(2500);
  elbow.stop();
  clawClose();
  delay(1000);
  elbow.open();
  delay(2000);
  elbow.stop();
  clawOpen();
  delay(1000);

}

/*
  - stand
  - blocking function
   ---------------------------------------------------------------------------*/
void robot::goBack() {
  ReadIR();
  while (centerS == 0) {
    turnRight();
    ReadIR();
  }
}

/*
  - stand
  - blocking function
   ---------------------------------------------------------------------------*/
void robot::junction() {
  int JuncTime = 200;
  switch (count) {
    case 1:
      junctionNum++;
      forward(lineSpeed);
      delay(JuncTime);
      stop();
      ReadIR();
      while (centerS == 1) {
        turnRight();
        ReadIR();

    } while (centerS == 0) {
        turnRight();
        ReadIR(); 

      }
      goBack();
      break;      // follow main line, hit 111 go to right junction and go back
    
    case 2:
      forward(200);
      delay(JuncTime);
      ReadIR();
      break;    // while going back from the 1st junction, ignore 111
      
    case 3:
      forward(lineSpeed);
      delay(JuncTime);
      ReadIR();
      while (centerS == 1) {
        turnLeft();
        ReadIR();

      } while (centerS == 0) {
        turnLeft();
        ReadIR();
        count = 0;  // reset junction count
      }
      break;     // While going back from the 2 junction, turnLeft for main line
  }
}

/*
  - stand
  - blocking function
   ---------------------------------------------------------------------------*/
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
    houseNum++;
    delay(1000);
    ultrasonicRead();
    grabnLiftCup();
    ReadIR();

  } 

}