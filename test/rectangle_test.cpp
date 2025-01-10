/**
 * @file rectangle_test.cpp
 * @brief This file contains the implementation for testing the movement of the robot in a rectangle path.
 * @author kyranth
 * @date 2019-07-26
 *
 * This program tests and calibrates the movement of the robot in a rectangle path by moving forward, left and right point turns.
 */

#include <Arduino.h>
#include "robot.h"
#include "sensor.h"

int leftmotorPin9B = 9;
int leftmotorPin10F = 10;

int rightmotorPin5F = 5;
int rightmotorPin6B = 6;

void setup()
{
    pinMode(leftmotorPin9B, OUTPUT);
    pinMode(leftmotorPin10F, OUTPUT);
    pinMode(rightmotorPin5F, OUTPUT);
    pinMode(rightmotorPin6B, OUTPUT);
}

void loop()
{
    forward(240, 2000);
    clockwise_rotate();
    delay(650);
    forward(240, 2000);
    clockwise_rotate();
    delay(650);
    forward(240, 2000);
    clockwise_rotate();
    delay(650);
    forward(240, 2000);
    clockwise_rotate();
    delay(650);
}

void clockwise_rotate()
{
    analogWrite(leftmotorPin9B, LOW);
    analogWrite(leftmotorPin10F, 200);

    analogWrite(rightmotorPin5F, LOW);
    analogWrite(rightmotorPin6B, 200);
}

void anticlockwise_rotate()
{
    analogWrite(leftmotorPin9B, 200);
    analogWrite(leftmotorPin10F, LOW);

    analogWrite(rightmotorPin5F, 200);
    analogWrite(rightmotorPin6B, LOW);
}

void forward(int driveSpeed, int driveTime)
{
    analogWrite(leftmotorPin10F, driveSpeed);
    analogWrite(rightmotorPin5F, driveSpeed);
    analogWrite(leftmotorPin9B, LOW);
    analogWrite(rightmotorPin6B, LOW);
    delay(driveTime);
}

void stopMotor()
{
    analogWrite(leftmotorPin10F, LOW);
    analogWrite(rightmotorPin5F, LOW);
    analogWrite(leftmotorPin9B, LOW);
    analogWrite(rightmotorPin6B, LOW);
}
