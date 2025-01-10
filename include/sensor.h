
#ifndef SENSOR_H
#define SENSOR_H

class sensor {

 private:
   // private memebers
   int _sensorPin;
// byte _ultraSonicPin;
// byte _IRPin;
// byte _proximityPin;

 public:
   // public member
   sensor(int sensorPin);
   int DRead();

};

#endif
