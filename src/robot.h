#include "motor.h"
#include "sensor.h"
#include <Arduino.h>

class robot {
private:

public:
	int count = 0;
	int centimeters;
	robot();
	void myDelay(int del);
	void begin();
	void countHouse();
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
	void gotoSorting();
	void startAgain();
	void junction();
	void followLine();
	void sortCup();
	
};
