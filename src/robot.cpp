#include "robot.h"
#include "motor.h"
#include "sensor.h"
#include <Arduino.h>
#include <HCSR04.h>

// Configuration
byte leftS = 1, centerS = 1, rightS = 1;
byte cupleftIR = 1, cuprightIR = 1;
byte rightCup = 0, leftCup = 0;

byte junctionNum = 0, houseNum = 0;

byte cupColor = 0;
byte lineSpeed = 180;


byte blackCup, whiteCup, blackNwhite;

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

robot::robot(){ }

void robot::myDelay(int del) {
  unsigned long myPrevMillis = millis();
  while (millis()- myPrevMillis <= del);
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
  myDelay(500);
  claw.open();
  myDelay(1500);
  claw.stop();
}

/*
  - open claw
  - clawState = 0
   ---------------------------------------------------------------------------*/
void robot::clawOpen(int interval) {
  claw.open();
  delay(interval);
  claw.stop();
  clawState = 0;
} 

/*
  - close claw
  - clawState = 0
   ---------------------------------------------------------------------------*/
void robot::clawClose(int interval) {
  claw.close();
  delay(interval);
  claw.stop();
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
  byte speed = 200;
  leftMotor.forward(speed);
  rightMotor.backward(speed);
}

/*
  - left motor backward
  - right motor forward
   ---------------------------------------------------------------------------*/
void robot::turnLeft() {
  byte speed = 200;
  leftMotor.backward(speed);
  rightMotor.forward(speed);
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
*/
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

/*
  - Read ultrasonic sensor
   ---------------------------------------------------------------------------*/
void robot::ultrasonicRead() {
  centimeters = distanceSensor.measureDistanceCm();
  // Serial.println(centimeters);
}


void robot::remainingCup() {
  readCupIR();
  while(max(0, blackCup)) {
    // sortingArea();
    cupColor = 2;
    cupState = 1;

  } while(max(0, whiteCup)) {
    // sortingArea();
    cupColor = 3;
    cupState = 1;
  }
   ultrasonicRead();
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
  if (centimeters > 7) {
    clawOpen(500);
    ultrasonicRead();
    readCupIR();

  } else if (centimeters < 7 && centimeters > 0) {
     switch (cupColor) {
      case 1:     //Black
        clawClose(200);
        cupState = 1;
        // remainingCup();
        break;

      case 2:    // white
        backward(speed);
        delay(200);

        // remainingCup();
        goBack();
        break;

      case 3:   //Back & White
        backward(speed);
        delay(200);

        // remainingCup();
        goBack();
        break;

      default:  //No cups 
        backward(speed);
        delay(200);

        // remainingCup();
        goBack();
        break;
     }

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
    delay(1500);
    elbow.stop();
    clawOpen(1000);
    elbow.open();
    delay(1500);
    elbow.stop();
    clawOpen(1000);
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
  clawClose(800);
  elbow.open();
  delay(2000);
  elbow.stop();
  clawOpen(800);

}

/*
  - stand
  - blocking function
*/
void robot::goBack() {
  byte speed = 100;
  ReadIR();
  backward(speed);
  delay(180);
  while (rightS == 0) {
    turnRight();
    ReadIR();
  }
  lineSpeed = 180;
}

/*
  - stand
  - blocking function
*/
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
      lineSpeed = 100;
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

void robot::sortingArea() {
  if(count == 1) {
    switch (cupColor) {
    case 1:
      stop();
      putBack();
      break;

    case 2:
      turnRight();
      followLine();

    case 3:
      turnLeft();
      followLine();
    
    default:
      break;
    }

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
    lineSpeed = 100;
    junction();
    ReadIR();

  } else if (leftS == 0 && centerS == 0 && rightS == 0) {
    stop();
    houseNum++;
    delay(500);
    ultrasonicRead();
    grabnLiftCup();
    ReadIR();

  } 

}
