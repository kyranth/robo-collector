
#include "Arduino.h"

class motor {
  private:
    byte _CW;
    byte _CCW;

  public:
    // public members
    motor(byte CW, byte CCW);

    // backward is CW - LOW, CCW - driveSpeed
    void backward(int driveSpeed);

    // forward is CW - LOW, CCW - driveSpeed
    void forward(int driveSpeed);

    void stop();

};
