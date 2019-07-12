class sensor {

	// class memebers
	

private:
	// private memebers
	

public:
	// public members
	void setSensor(byte sensorPin) {
		pinMode(sensorPin, INPUT);

	}
 
/*
	void sensorRead (byte sensorPin, byte mode) {

		switch (mode) {
		    case digital:
		      // do something
		      digitalRead(sensorPin);
		      break;
		    case analog:
		      // do something
		      analogRead(sensorPin);
		      break;
		    default:
		      // do something
		      Serial.println("Specified Mode is Invalid!");
		}


		
	}
*/
	
};
