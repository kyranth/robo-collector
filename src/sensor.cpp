#include "sensor.h"
#include "Arduino.h"

sensor::sensor(byte sensorPin) {
    _sensorPin = sensorPin;
    pinMode(sensorPin, INPUT);

}

void sensor::sensorDRead(byte sensorPin) {
    int value = digitalRead(_sensorPin);
    Serial.print("");
}
