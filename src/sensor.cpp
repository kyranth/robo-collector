#include "sensor.h"
#include "Arduino.h"

sensor::sensor(int sensorPin) {
    _sensorPin = sensorPin;
    pinMode(sensorPin, INPUT);

}

int sensor::sensorDRead() {
    int value = digitalRead(_sensorPin);
    Serial.print("");
    return value;
}
