#include "motor.h"
#include "sensor.h"
#include <Arduino.h>

class robot {
private:

public:
	int count = 0;
	int centimeters;
	robot();
	void begin();
	void clawOpen(int interval);
	void clawClose(int interval);
	void forward(int driveSpeed);
	void backward(int driveSpeed);
	void turnLeft();
	void turnRight();
	void stop();

	void readCupIR();
	void ultrasonicRead();
	void grabnLiftCup();
	void putBack();
	void ReadIR();
	void grabCup();
	void goBack();
	void sortingArea();
	void junction();
	void remainingCup();
	void followLine();
	void cupCollect();
	
};
