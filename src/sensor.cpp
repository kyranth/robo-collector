/**
 * @file sensor.cpp
 * @brief Implementation of the sensor
 * @author S Khan
 * @date 2019-07-26
 *
 * This file contains the implementation of the sensor.
 */

#include "sensor.h"
#include "Arduino.h"

sensor::sensor(int sensorPin)
{
    _sensorPin = sensorPin;
    pinMode(sensorPin, INPUT);
}

int sensor::DRead()
{
    int value = digitalRead(_sensorPin);
    // Serial.print(value);
    return value;
}
