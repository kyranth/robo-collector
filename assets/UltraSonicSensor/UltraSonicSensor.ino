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
