
#ifndef MOTOR_H
#define MOTOR_H

class motor {
  private:
    int CW;
    int CCW;

  public:
    // public members
    motor(int _CW, int _CCW);

    // backward is CW - LOW, CCW - driveSpeed
    void backward(int driveSpeed);

    // forward is CW - LOW, CCW - driveSpeed
    void forward(int driveSpeed);

    void stop();

};

#endif
