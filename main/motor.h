
class motor {
	protected:
	  byte _CW;
	  byte _CCW;

public:
	byte CW;
	byte CCW;

	// public members
	motor(byte CW, byte CCW); // CW, CCW

	// backward is CW - LOW, CCW - driveSpeed
	void backward(byte driveSpeed) {
		analogWrite(CW, driveSpeed);
		analogWrite(CCW, LOW);
		Serial.println("---backward executed---");
		delay(10);
	}

	// forward is CW - LOW, CCW - driveSpeed
	void forward(byte driveSpeed) {
		analogWrite(CW, LOW);
		analogWrite(CCW, driveSpeed);
		Serial.println("---forward executed---");
		delay(10);
	}

	void stop() {
		analogWrite(CW, LOW);
		analogWrite(CCW, LOW);
		Serial.println("---stopped---");
		delay(10);
	}
	
};

motor::motor(byte CW, byte CCW) {
	_CW = CW;
	_CCW = CCW;
	pinMode(CW, OUTPUT);
	pinMode(CCW, OUTPUT);
}
