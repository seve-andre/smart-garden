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

   private:
    int speed;
    ServoMotor* servo;
    long irrigationTime;
};

#endif