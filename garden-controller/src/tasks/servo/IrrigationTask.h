#ifndef __IRRIGATE_TASK__
#define __IRRIGATE_TASK__

#include "components/servo/ServoMotor.h"
#include "tasks/Task.h"

class IrrigationTask : public Task {
   public:
    IrrigationTask();
    void tick();
    enum State { IDLE,
                 ONGOING,
                 PAUSE,
                 COMPLETED } state;
    void reset();

    int speed;
    ServoMotor* servo;
    long irrigationTime;
    unsigned int pos;
    void startServo();
    void moveServoTo180();
    void moveServoTo0();
    void stopServo();
    void timerServo();
    void sleepIrrigation();

    bool firstTimerInit;
    bool startServoTo180;
    bool activeServo;
    bool startServoTo0;
    unsigned long tStop;
    unsigned long tServo;
    unsigned long tSleep;
};

#endif