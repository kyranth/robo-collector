#include "motor.h"
#include "sensor.h"
#include <Arduino.h>

class robot {
private:

public:
	int count;
	robot();
	void begin();
	void forward(int driveSpeed);
	void backward(int driveSpeed);
	void turnLeft();
	void turnRight();
	void stop();
	void ReadIR();
	void manualControl();
	void setColor(int redPin, int greenValue, int blueValue);
	int rgbFlash(String color);
	void followLine();
	void followLineIT();
	void CheckForCup();
};
