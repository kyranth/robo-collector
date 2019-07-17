/*
    JEFF BOB THE 3RD(Clawbot)
    License: iTEST NYU Robotis Course
    TEAM: {
      Dr. Walkot, Mr. Kiefer, Shafiqur Khan, Nishal Thapa
      Lena Khosrof, Yanni, Dishan
    }

    Configuration:
    Left Motor(10, 9)   leftColorSensor(11)     rightColorSensor(13)
    Right Motor(6, 6)   centerColorSensor(12)   IRSensor()
    RGB Led(2, 3, 4)    

 */

#include <IRremote.h>
#include "motor.h"
#include "sensor.h"
#include "robot.h"

int defualtSpeed = 80;


int sensorleft = 11;
int sensorcenter = 12;
int sensorright = 13;
int leftS = 1;
int centerS = 1;
int rightS = 1;

int redPin = 3;
int greenPin = 4;
int bluePin = 2;

const byte RECV_PIN = 7;
IRrecv irrecv(RECV_PIN);
decode_results results;
unsigned long key_value = 0;

robot jeffbobthe3rd;
motor leftMotor(10, 9); // CW, CCW
motor rightMotor(6, 5);
motor elbow(A0, A1);
motor claw(A2, A3);

/*
void lastSensor(){
  int leftSensorState = digitalRead(sensorleft);
  int rightSensorState = digitalRead(sensorcenter);
  int leftSensorState = digitalRead(sensorright);
  int lastSensorState;
}
*/

void robotForward(int driveSpeed) {
  leftMotor.forward(driveSpeed);
  rightMotor.forward(driveSpeed);
  // Serial.println("---forward executed---");
  // delay(10);
  }

void robotBackward(int driveSpeed) {
  leftMotor.backward(driveSpeed);
  rightMotor.backward(driveSpeed);
  // Serial.println("---backward executed---");
  // delay(10); 
  }

void turnLeft() {
<<<<<<< HEAD
  leftMotor.backward(200);
  rightMotor.forward(200);
  // delay(turnAngle); 
  }

void turnRight() {
  leftMotor.forward(200);
  rightMotor.backward(200);
  //delay(turnAngle); 
=======
  leftMotor.forward(240);
  rightMotor.forward(240);
  }

void turnRight() {
  leftMotor.backward(240);
  rightMotor.backward(240);
>>>>>>> 668a3be4fb407156d58c6974e061b31abe911bed
  }

void setColor(int redValue, int greenValue, int blueValue) {
  analogWrite(redPin, redValue);
  analogWrite(greenPin, greenValue);
  analogWrite(bluePin, blueValue); }

void flash() {
  setColor(0, 200, 0);
  delay(100);
  setColor(0, 0, 0);
  delay(100); }

void setup () {
  jeffbobthe3rd.begin();
  pinMode(sensorleft, INPUT);
  pinMode(sensorcenter, INPUT);
  pinMode(sensorright, INPUT);
}

void loop() {
	leftS = digitalRead(sensorleft);
  //Serial.print("leftS: ");
  //Serial.println(leftS);
  //delay(200);

  centerS = digitalRead(sensorcenter);
  //Serial.print("centerS: ");
  //Serial.println(centerS);
  //delay(200);

  rightS = digitalRead(sensorright);
  //Serial.print("rightS: ");
  //Serial.println(rightS);
  //delay(200);
  
  while (leftS == 0 && centerS == 1 && rightS == 0) {
    robotForward(defualtSpeed);
    flash();

  } while ((centerS == 1) || (leftS == 0 && rightS == 0)) {
    robotForward(defualtSpeed);
    flash();

<<<<<<< HEAD
  } else if(rightS == 1 && centerS == 0 && leftS == 0) {
    turnRight();
    setColor(0, 0, 200);

  } else if(leftS == 1 && centerS == 0 && rightS == 0) {
    turnLeft();
    setColor(0, 0, 200);

  } else if(leftS == 0 && centerS == 0 && rightS == 0) {
=======
  } while (rightS == 1 && centerS == 0 && leftS == 0) {
    turnRight();
    setColor(0, 0, 200);

  } while (leftS == 1 && centerS == 0 && rightS == 0) {
    turnLeft();
>>>>>>> 668a3be4fb407156d58c6974e061b31abe911bed
    setColor(200, 0, 0);

  } while (leftS == 1 && centerS == 1 && rightS == 1) {
    turnRight();

  } while(leftS == 0 && centerS == 0 && rightS == 0) {
    setColor(200, 200, 200);
    if (leftS == 1 || centerS == 1 || rightS == 1) {
      
    }
   
  }
}

// claw.forward(70);
// delay(1000);
// claw.stop();
