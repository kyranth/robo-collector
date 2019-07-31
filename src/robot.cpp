#include "robot.h"
#include "motor.h"
#include "sensor.h"
#include <Arduino.h>
#include <HCSR04.h>

// Configuration
bool juncState;
byte leftS = 1, centerS = 1, rightS = 1, jIR = 1;
byte cupleftIR = 1, cuprightIR = 1;
byte rightCup = 0, leftCup = 0;

byte juncNum = 0, lap = 0;
byte cupColor = 0;
byte lineSpeed = 180;
const byte juncMax = 6;

byte blackCup = 0, whiteCup = 0, black_N_whiteCup = 0;
byte clawState, cupState, elbowState;

motor leftMotor(10, 9); // CW, CCW
motor rightMotor(6, 5);
motor elbow(2, 4);
motor claw(7, 8);

sensor leftIR(A0);
sensor centerIR(A1);
sensor rightIR(A2);
sensor junctionIR(A5);
sensor cupSensorRight(11);
sensor cupSensorLeft(12);

UltraSonicDistanceSensor distanceSensor(A4, A3);

robot::robot(){ }

void robot::myDelay(unsigned long del) {
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
  juncState = true;
}

void robot::juncCheck() {
  juncNum++;
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
  byte speed = 250;
  leftMotor.forward(speed);
  rightMotor.backward(speed);
}

void robot::turnLeft() {
  byte speed = 250;
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
  jIR = junctionIR.DRead();
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
    for (int i = 0; i > 0; i++) {
      whiteCup++;
    }
    
  }
  else if ((leftCup == 1 && rightCup == 0) || (leftCup == 0 && rightCup == 1)){   // Black & White = Everything else
    // go to everything else
    cupColor = 3;
    black_N_whiteCup++;

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

void robot::getOut() {
  goBack();
  if (counter == 4) {
    forward(180);
    myDelay(100);
    counter = 5;
  } if (counter == 5) {
    while (leftS == 1) {
      turnRight();
      counter = 0;
    }
    followLine();
  }
}

void robot::inSorting() {
  if (juncNum == (juncMax + 1) && blackCup > 0) {
    readCupIR();
    if (counter == 1) {
      juncState = false;
      stop();
      putBack();
      counter = 4;
      getOut();
      lap = 2;
    } else { }

  } else if (juncNum == juncMax && whiteCup > 0) {
    if (counter == 1) {
      // directions

      putBack();
      counter = 4;
      getOut();
      lap = 3;
    } else { }

  } else if (juncNum == juncMax && black_N_whiteCup > 0) {
    if (counter == 1) {
      // directions

      putBack();
      counter = 4;
      getOut();
    } else { }
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
      case 2:    // white cup
        if (lap == 2) {
          clawClose(200);
          cupState = 1;
        } else {
          backward(speed);
          myDelay(200);
          goBack();
        }
        break;

      case 3:
        //Black & White cup
        if (lap == 3) {
          clawClose(200);
          cupState = 1;
        } else {
          backward(speed);
          myDelay(200);
          goBack();
        }
        break;

      default:
        // black cup
        clawClose(200);
        cupState = 1;   // for grab_N_Lift
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
void robot::grab_N_LiftCup() {
  grabCup();
  if (cupState == 1) {
    elbow.close();
    myDelay(1500);
    elbow.stop();
    elbowState = 1;
    clawOpen(1000);
    elbow.open();
    myDelay(1500);
    elbow.stop();
    clawOpen(1000);
    elbowState = 0;
    cupState = 0;
    readCupIR();

  } else {
    cupState = 0;
    readCupIR();
    ultrasonicRead();

  }
}


void robot::goBack() {
  ReadIR();
  while (rightS == 0) {
    turnRight();
    ReadIR();
  }
  lineSpeed = 180;
}

void robot::junction() {
  Serial.println("Junction");
  switch (counter) {
    case 1:
      juncCheck();
      inSorting();
      ReadIR();
      while (jIR == 0) {
        forward(lineSpeed);
        ReadIR();
      } 
      stop();
      myDelay(5);
      while (centerS == 1) {
        turnRight();
        ReadIR();
      }
      stop();
      myDelay(5);

      while (centerS == 0) {
        turnRight();
        ReadIR();
      }
      stop();
      myDelay(5);

      lineSpeed = 100;
      break;      // follow main line, hit 111 go to right junction and go back
    
    case 2:
      while(centerS == 1) {
        forward(lineSpeed);
        ReadIR();  
      }
      // stop();
      myDelay(5);
      ReadIR();
      lineSpeed = 100;
      break;    // while going back from the 1st junction, ignore 111
      
    case 3:
      ReadIR();
      while (jIR == 0) {
        forward(lineSpeed);
        ReadIR();
      } 
      stop();
      myDelay(5);
      while (centerS == 1) {
        turnLeft();
        ReadIR();
      }
      stop();
      myDelay(5);

      while (centerS == 0) {
        turnLeft();
        ReadIR();
      }
      stop();
      myDelay(5);
      counter = 0;
      lineSpeed = 180;

      break;          // While going back from the 2 junction, turnLeft for main line
  }
}

void robot::followLine() {
  ReadIR();
  while(leftS == 0 && centerS == 1 && rightS == 0) {
    forward(lineSpeed);
    ReadIR();
  }
  stop();
  myDelay(5);
  while (leftS == 0 && rightS == 1) {
    turnRight();
    ReadIR();
  } 
  stop();
  myDelay(5);
  while (leftS == 1 && rightS == 0) {
    turnLeft();
    ReadIR();
  }
  stop();
  myDelay(5);
  if (leftS == 1 && centerS == 1 && rightS == 1) {
    counter++;
    Serial.println(counter);
    myDelay(100);
    if (juncState == true) {
      junction();
    }
    ReadIR();
  }
  if (leftS == 0 && centerS == 0 && rightS == 0) {
    stop();
    myDelay(500);
    ultrasonicRead();
    grab_N_LiftCup();
    ReadIR();
  }
}
