#include "robot.h"
#include "motor.h"
#include "sensor.h"
#include <Arduino.h>
#include <HCSR04.h>

// Configuration
byte leftS = 1, centerS = 1, rightS = 1;
byte cupleftIR = 1, cuprightIR = 1;
byte rightCup = 0, leftCup = 0;

byte junctionNum = 0, houseNum = 0, maxHouse = 12;

byte cupColor = 0;
byte lineSpeed = 150;

byte blackCup, whiteCup, blackNwhite;
byte clawState, cupState, elbowState;

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

robot::robot(){ }

void robot::myDelay(int del) {
  unsigned long myPrevMillis = millis();
  while (millis()- myPrevMillis <= del);
}

void robot::begin(){
	Serial.begin(9600);
	Serial.println("Robot Ready");
  pinMode(13, OUTPUT);

  claw.close();
  myDelay(500);
  claw.open();
  myDelay(1500);
  claw.stop();
}

void robot::countHouse() {
  houseNum = houseNum + 2;
  digitalWrite(13, HIGH);
  myDelay(100);
  digitalWrite(13, LOW);
}

void robot::clawOpen(int interval) {
  claw.open();
  myDelay(interval);
  claw.stop();
  clawState = 0;
} 

void robot::clawClose(int interval) {
  claw.close();
  myDelay(interval);
  claw.stop();
  clawState = 1;
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
  byte speed = 200;
  leftMotor.forward(speed);
  rightMotor.backward(speed);
}

void robot::turnLeft() {
  byte speed = 200;
  leftMotor.backward(speed);
  rightMotor.forward(speed);
}

void robot::stop() {
  leftMotor.stop();
  rightMotor.stop();
}

//****************************************************************************************************************************************************

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
    blackCup++;
  }
  else if (leftCup == 0 && rightCup == 0) { // White = Paper
    // go to paper
    cupColor = 2;
    whiteCup++;
  }
  else if ((leftCup == 1 && rightCup == 0) || (leftCup == 0 && rightCup == 1)){   // Black & White = Everything else
    // go to everything else
    cupColor = 3;
    blackNwhite++;

  } else {
    cupColor = 0;

  }
}

void robot::ultrasonicRead() {
  centimeters = distanceSensor.measureDistanceCm();
  // Serial.println(centimeters);
}

void robot::putBack() {
  elbow.close();
  myDelay(1550);
  elbow.stop();
  clawClose(800);
  elbow.open();
  myDelay(1250);
  elbow.stop();
  clawOpen(800);

}

void robot::sortingArea() {
  readCupIR();
    if(count == 1) {
      switch(cupColor) {
      case 1:
        // followLine(0);
        stop();
        putBack();
        break;

      case 2:
        turnRight();
        // followLine(0);

      case 3:
        turnLeft();
        // followLine(0);
    
      default:
        break;
      }
    }
}

void robot::gotoSorting() {
  if (houseNum == (maxHouse + 2) && blackCup > 0) {
    sortingArea();
  }
}

/*
  - Checks to see if there is a cup in front of the robot
  - Checks to see what type of cup is in front of the robot
  - If nothing is within 7 cm, the claw opens
  - The claw opens for 1 sec
  - If something is within 7 cm, the claw closes
  - The claw closes for 200 ms
  - When cupState is 1, the robot is lifting the cup
  - Case 1 checks to see if there are black cups (plastic)
  - Case 2 checks to see if there are white cups (paper)
  - Case 3 checks to see if there are black and white cups (everything else)
  - Default checks to see if there are no cups (the robot goes back and looks for cups)
   ---------------------------------------------------------------------------*/
void robot::grabCup() {
  byte speed = 100;
  ultrasonicRead();
  readCupIR();
  if (centimeters < 7 && centimeters > 0) {
    switch (cupColor) {
      case 1:     //Black
        clawClose(200);
        cupState = 1;
        // remainingCup();
        break;

      case 2:    // white
        backward(speed);
        myDelay(200);

        // remainingCup();
        goBack();
        break;

      case 3:   //Back & White
        backward(speed);
        myDelay(200);

        // remainingCup();
        goBack();
        break;

      default:  //No cups 
        backward(speed);
        myDelay(200);

        // remainingCup();
        goBack();
        break;
    }
  } else {
    ultrasonicRead();
    readCupIR();
    goBack();
  } 

}

/*
  - Grabs cup if within 7 cm
  - Lifts cup upto the holder
  - Elbow open is when the arm is lifted up
  - Elbow close is when the arm is in its regular position
  - Elbow stop is when the arm stops moving
  - The elbow opens for 1.5 secs
  - The elbow closes for 1.5 secs
  - The elbow stops for 1.5 secs
  - The claw opens for 1 sec
  - This function is executed after the grab cup function is executed
   ---------------------------------------------------------------------------*/
void robot::grabnLiftCup() {
  grabCup();
  if (cupState == 1) {
    elbow.close();
    myDelay(1500);
    elbow.stop();
    clawOpen(1000);
    elbow.open();
    myDelay(1500);
    elbow.stop();
    clawOpen(1000);
    elbowState = 1;
    cupState = 0;
    readCupIR();

  } else {
    cupState = 0;
    readCupIR();
    ultrasonicRead();

  }
}

void robot::startAgain() {
  
}

void robot::goBack() {
  byte speed = 100;
  ReadIR();
  backward(speed);
  myDelay(180);
  while (rightS == 0) {
    turnRight();
    ReadIR();
  }
  lineSpeed = 180;
}

void robot::junction() {
  int JuncTime = 200;
  switch (count) {
    case 1:
      countHouse();
      gotoSorting();
      forward(lineSpeed);
      myDelay(JuncTime);
      stop();
      ReadIR();
      while (centerS == 1) {
        turnRight();
        ReadIR();

    } while (centerS == 0) {
        turnRight();
        ReadIR();
        
    }
      lineSpeed = 100;
      break;      // follow main line, hit 111 go to right junction and go back
    
    case 2:
      forward(lineSpeed);
      myDelay(JuncTime);
      ReadIR();
      lineSpeed = 100;
      break;    // while going back from the 1st junction, ignore 111
      
    case 3:
      forward(lineSpeed);
      myDelay(JuncTime);
      ReadIR();
      while (centerS == 1) {
        turnLeft();
        ReadIR();

      } while (centerS == 0) {
        turnLeft();
        ReadIR();
        count = 0;  // reset junction count
      }
      break;          // While going back from the 2 junction, turnLeft for main line
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
    myDelay(500);
    ultrasonicRead();
    ReadIR();
    grabnLiftCup();

  }
}
