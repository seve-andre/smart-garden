#ifndef __SERVO_TASK__
#define __SERVO_TASK__

#include "Task.h"
#include "servo_motor_impl.h"

class ServoTask: public Task {
  public:
    ServoTask(int pin);
    void beginningDrinkOut();
    void startServo(unsigned int n_drink);
    void moveServoTo180(); // goes from 0 degrees to 180 degrees
    void moveServoTo0(); // goes from 0 degrees to 180 degrees
    void printMessageDrinkReady(unsigned int n_drink);
    void tick();
    void stopServo();
    void timerServo();
    
  private:
    ServoMotorImpl* pMotor;
    enum {PRODUCT_NOT_READY, PRODUCT_READY} stateProduct;

    unsigned int n_drink;
    unsigned volatile int pos;
    bool startServoTo180;
    bool startServoTo0;
};

#endif
