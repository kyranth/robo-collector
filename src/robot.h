#include "motor.h"
#include "sensor.h"
#include <Arduino.h>

class robot
{
private:
public:
	int counter = 0, centimeters;
	robot();
	void myDelay(unsigned long del);
	void begin();
	void jCount();
	void clawOpen(int interval);
	void clawClose(int interval);
	void forward(int driveSpeed);
	void backward(int driveSpeed);
	void turnLeft();
	void hardLeft();
	void turnRight();
	void hardRight();
	void stop();

	void ReadIR();
	void readCupIR();
	void ultrasonicRead();
	void grab_N_LiftCup();
	void putBack();
	void getCupData();
	void grabCup();
	void goBack();
	void getOut();
	void inSorting();
	void junction();
	void followLine();
	void printArr();
	void junctionProtocol();
};
