#include <Arduino.h>
#include "motor.h"

class robot
{
public:
	int counter = 0;
	float centimeters;
	byte leftS = 1, centerS = 1, rightS = 1, jIR = 1;
	byte cupleftIR = 1, cuprightIR = 1;
	byte rightCup = 0, leftCup = 0;
	byte juncNum = 0, lap = 0;
	byte clawState, cupState, elbowState;
	byte cupColor = 0, blackCup = 0, whiteCup = 0, black_N_whiteCup = 0;
	robot();
	void myDelay(unsigned long del);
	void initiate();
	void jCount();
	void clawOpen(int interval);
	void clawClose(int interval);
	void forward(byte driveSpeed);
	void backward(byte driveSpeed);
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
	void dropNlap();
	void manualControl();
};
