#include "Arduino.h"

class sensor {

 private:
   // private memebers
   byte _sensorPin;
// byte _ultraSonicPin;
// byte _IRPin;
// byte _proximityPin;


 public:
   // public member
   sensor(byte sensorPin);
   void sensorDRead(byte sensorPin);

};

