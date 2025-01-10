#ifndef MOTOR_H
#define MOTOR_H

class motor {
  private:
    int _CW;
    int _CCW;

  public:
    // public members
    motor(int CW, int CCW);

    // backward is CW - LOW, CCW - driveSpeed
    void backward(int driveSpeed);

    // forward is CW - LOW, CCW - driveSpeed
    void forward(int driveSpeed);
    void open();
    void close();
    void stop();

};

#endif
