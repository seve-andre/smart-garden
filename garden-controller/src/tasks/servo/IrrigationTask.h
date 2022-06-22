#ifndef __IRRIGATE_TASK__
#define __IRRIGATE_TASK__

#include "components/servo/ServoMotor.h"
#include "tasks/Task.h"

class IrrigationTask : public Task {
   public:
    IrrigationTask();
    void tick();
    enum State { IDLE, ONGOING, PAUSE, COMPLETED } state;
    void setSpeed(int speed);
    void resetStopTimer();

   private:
    int speed;
    ServoMotor* servo;
    long irrigationTime;
    int pos;
    void startServo();
    void moveServoTo180();
    void stopServo();
    void timerServo();
    void sleepIrrigation();

    bool firstTimerInit;
    bool startServoTo180;
    bool activeServo;
    bool startServoTo0;
    long tStop;
    long tServo;
    long tSleep;
};

#endif