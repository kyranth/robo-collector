#include "motor.h"
#include "sensor.h"
#include <Arduino.h>

class robot {
private:

public:
	robot();
	void begin();
	void forward(int driveSpeed);
	void backward(int driveSpeed);
	void turnLeft();
	void turnRight();
	void manualControl();
	void setColor(int redPin, int greenValue, int blueValue);
	int rgbFlash(String color);
	void followLine();
};
