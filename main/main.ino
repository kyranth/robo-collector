
#include <IRremote.h>
#include "motor.h"
#include "sensor.h"

const byte RECV_PIN = 4;
IRrecv irrecv(RECV_PIN);
decode_results results;
unsigned long key_value = 0;

motor leftMotor(10, 9);
motor rightMotor(6, 5);

void robotForward(byte driveSpeed, byte driveTime) {
	leftMotor.forward(driveSpeed);
	rightMotor.backward(driveSpeed);
	delay(driveTime);
	leftMotor.stop();
	rightMotor.stop();

}

void robotBackward(byte driveSpeed, byte driveTime){
  leftMotor.backward(driveSpeed);
  rightMotor.forward(driveSpeed);
  delay(driveTime);
  leftMotor.stop();
  rightMotor.stop();
}

void setup () {
	Serial.begin(9600);

}

//forward
//5 and 10
//backward 
//6 and 9

void loop() {
  robotForward(100, 1000);
 
}
