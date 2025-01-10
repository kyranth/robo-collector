/**
 * @file ultrasonic_sensor_test.cpp
 * @brief This file contains the implementation for interfacing with an ultrasonic sensor.
 * @author kyranth
 * @date 2019-07-26
 *
 * This program tests the HCSR04 library to interface with an ultrasonic sensor. The sensor is used to measure the distance between the sensor and an object.
 */

#include <Arduino.h>
#include <HCSR04.h>

UltraSonicDistanceSensor distanceSensor(A3, A4);  // Initialize sensor that uses digital pins A3 & A4.

void setup () {
    Serial.begin(9600);  // We initialize serial connection so that we could print values from sensor.
}

void loop () {
    // Every 500 miliseconds, do a measurement using the sensor and print the distance in centimeters.
    Serial.println(distanceSensor.measureDistanceCm());
    int centimeters = distanceSensor.measureDistanceCm();
    int inches = centimeters / 2.54;
    Serial.println(inches);
    delay(500);

    if(inches <= 3)
    {
      // Close claw motor
    }
}
