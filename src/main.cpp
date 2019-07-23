/*
    JEFF BOB THE 3RD(Clawbot)
    License: iTEST NYU Robotis Course
    TEAM: {
      Dr. Walkot, Mr. Kiefer, Shafiqur Khan, Nishal Thapa
      Lena Khosrof, Yanni, Dushan Persaud
    }

    Configuration:
    Left Motor(10, 9)     leftColorSensor(11)       rightColorSensor(13)
    Right Motor(6, 6)     centerColorSensor(12)     IRSensor()
    ClawMotor(7, 8)       elbowMotor(2, 4)          RGB Led(11, 12, 13)

 */


#include "motor.h"
#include "sensor.h"
#include "robot.h"


robot rad;

void setup () {
  rad.begin();

}


void loop() {
  rad.goBack();
  
}

