#include "motor.h"
#include "sensor.h"
#include "Arduino.h"

class robot {
private:

public:
	robot();
	void robotForward(int driveSpeed, int driveTime);
	void robotBackward(int driveSpeed, int driveTime);
	void turnLeft(int turnAngle);
	void turnRight(int turnAngle);
};
