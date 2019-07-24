#include "motor.h"
#include "sensor.h"
#include <Arduino.h>

class robot {
private:

public:
	int count = 0;
	int centimeters;
	int juncVar;
	robot();
	void begin();
	void clawOpen();
	void clawClose();
	void forward(int driveSpeed);
	void backward(int driveSpeed);
	void turnLeft();
	void turnRight();
	void stop();
	void ReadIR();
	void grabCup();
	void goBack();
	void junction();
	void followLine();
	void followLineIT();
	void CheckForCup();
	void trashCollect();
};
