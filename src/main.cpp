/**
 * @file main.cpp
 * @brief Main file for the Scorpion robot
 * @author S Khan, Lena Khoshrof, John (Yanni) Kitsios
 * @date 2019-07-26
 *
 * Pinout configuration on an Arduino Uno:
 *
 * Left Motor(10, 9)     leftColorSensor(11)       rightColorSensor(13)
 * Right Motor(6, 6)     centerColorSensor(12)     IRSensor()
 * ClawMotor(7, 8)       elbowMotor(2, 4)          RGB Led(11, 12, 13)
 *
 * This file contains the main function that initializes the robot and enters the manual control loop.
 */

#include "robot.h"

robot scorpion;

void setup()
{
  scorpion.initiate();
}

void loop()
{
  scorpion.manualControl();
}
