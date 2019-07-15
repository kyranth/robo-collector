/*
    JEFF BOB THE 3RD
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

int defualtSpeed = 100;

int sensorleft = 11;
int sensorcenter = 12;
int sensorright = 13;
int leftS = 1;
int centerS = 1;
int rightS = 1;

const byte RECV_PIN = 4;
IRrecv irrecv(RECV_PIN);
decode_results results;
unsigned long key_value = 0;

robot jeffbobthe3rd;
motor leftMotor(10, 9); // CW, CCW
motor rightMotor(6, 5);


void robotForward(int driveSpeed) {
  leftMotor.forward(driveSpeed);
  rightMotor.backward(driveSpeed);
  Serial.println("---forward executed---");
  delay(10);}

void robotBackward(int driveSpeed) {
  leftMotor.backward(driveSpeed);
  rightMotor.forward(driveSpeed);
  Serial.println("---backward executed---");
  delay(10); }

void turnLeft(int turnAngle) {
  leftMotor.forward(240);
  rightMotor.forward(240);
  delay(turnAngle); }

void turnRight(int turnAngle) {
  leftMotor.backward(240);
  rightMotor.backward(240);
  delay(turnAngle); }

void setup () {
  jeffbobthe3rd.begin();
  pinMode(sensorleft, INPUT);
  pinMode(sensorcenter, INPUT);
  pinMode(sensorright, INPUT);

}

void loop() {
  leftS = digitalRead(sensorleft);
  Serial.print("leftS: ");
  Serial.println(leftS);
  //delay(200);

  centerS = digitalRead(sensorcenter);
  Serial.print("centerS: ");
  Serial.println(centerS);
  //delay(200);

  rightS = digitalRead(sensorright);
  Serial.print("rightS: ");
  Serial.println(rightS);
  //delay(200);
  
  if(leftS == 0 && centerS == 1 && rightS == 0) {
    robotForward(defualtSpeed);

  } else if(centerS == 1) {
    robotForward(defualtSpeed);

  } else if(rightS == 1) {
    leftMotor.forward(defualtSpeed);

  } else if(leftS == 1) {
    rightMotor.forward(defualtSpeed);

  } else if(leftS == 0 && centerS == 0 && rightS == 0) {
    leftMotor.forward(defualtSpeed);
    delay(2000);
    if(leftS == 1 || centerS == 1 || rightS == 1) {
      leftMotor.stop();
    }
  }

}
