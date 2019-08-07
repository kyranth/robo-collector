#include "motor.h"
#include "sensor.h"
#include <Arduino.h>
#include <HCSR04.h>
#include <IRremote.h>

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

byte clawState, cupState, elbowState;

const byte RECV_PIN = 3;
IRrecv irrecv(RECV_PIN);
decode_results results;
unsigned long key_value = 0;

void myDelay(unsigned long del)
{
    unsigned long myPrevMillis = millis();
    while (millis() - myPrevMillis <= del)
        ;
}

void clawOpen(int interval)
{
    claw.open();
    myDelay(interval);
    claw.stop();
    clawState = 0;
}

void clawClose(int interval)
{
    claw.close();
    myDelay(interval);
    claw.stop();
    clawState = 1;
}

void forward(byte driveSpeed)
{
    leftMotor.forward(driveSpeed);
    rightMotor.forward(driveSpeed);
}

void backward(byte driveSpeed)
{
    leftMotor.backward(driveSpeed);
    rightMotor.backward(driveSpeed);
}

void turnRight()
{
    byte speed = 180;
    leftMotor.forward(speed);
    rightMotor.backward(speed);
}

void turnLeft()
{
    byte speed = 180;
    leftMotor.backward(speed);
    rightMotor.forward(speed);
}

void stop()
{
    leftMotor.stop();
    rightMotor.stop();
}