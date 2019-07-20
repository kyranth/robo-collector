#include "robot.h"
#include "motor.h"
#include "sensor.h"
#include <Arduino.h>


// Configuration
int lineSpeed = 125;

// LED Pins
int redPin = 11;
int greenPin = 12;
int bluePin = 13;

// Sensor Pins
int sensorleft = 11;
int sensorcenter = 12;
int sensorright = 13;
int leftS = 1;
int centerS = 1;
int rightS = 1;


motor leftMotor(10, 9); // CW, CCW
motor rightMotor(6, 5);

robot::robot(){

}

void robot::begin(){
	Serial.begin(9600);
	Serial.println("Robot Ready");
  pinMode(sensorleft, INPUT);
  pinMode(sensorcenter, INPUT);
  pinMode(sensorright, INPUT);
  pinMode(redPin, OUTPUT);
  pinMode(greenPin, OUTPUT);
  pinMode(bluePin, OUTPUT);
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

void robot::setColor(int redValue, int greenValue, int blueValue) {
  analogWrite(redPin, redValue);
  analogWrite(greenPin, greenValue);
  analogWrite(bluePin, blueValue); 
}

int robot::rgbFlash(String color) {
    if (color == "red") {
      setColor(200, 0, 0);
      delay(100);
      setColor(0, 0, 0);
      delay(100); 
    } else if (color == "green") {
      setColor(0, 200, 0);
      delay(100);
      setColor(0, 0, 0);
      delay(100); 
    } else if (color == "blue") {
      setColor(0, 0, 200);
      delay(100);
      setColor(0, 0, 0);
      delay(100);
    }
}

void robot::followLine() {
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
  
  if(leftS == 0 && centerS == 1 && rightS == 0) {
    forward(lineSpeed);
    rgbFlash("green");

  } else if (leftS == 0 && centerS == 1 && rightS == 1) {
    turnRight();

  } else if (leftS == 1 && centerS == 1 && rightS == 0) {
    turnLeft();

  } else if (leftS == 0 && centerS == 0 && rightS == 1) {
    setColor(0, 0, 200);
    turnRight();

  } else if (leftS == 1 && centerS == 0 && rightS == 0) {
    setColor(200, 0, 0);
    turnLeft();

  } else if (leftS == 1 && centerS == 1 && rightS == 1) {
    forward(lineSpeed);

  } else if (leftS == 0 && centerS == 0 && rightS == 0) {
    setColor(200, 200, 200);
    backward(lineSpeed);

  } else if (leftS == 1 && centerS == 0 && rightS == 1) {
    forward(lineSpeed);
  
  }
}

