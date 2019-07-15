#include "robot.h"
#include "motor.h"
#include "sensor.h"
#include "Arduino.h"

robot::robot(){
	
}

void robot::begin(){
	Serial.begin(9600);
	Serial.println("Robot Ready");
}
