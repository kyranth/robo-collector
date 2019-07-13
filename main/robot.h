#include "motor.h"
#include "sensor.h"

class robot {
private:

public:
	robot();
	void robotForward(int driveSpeed, int driveTime);
	void robotBackward(int driveSpeed, int driveTime);
	turnLeft(int turnAngle);
	turnRight(int turnAngle);
};
