#ifndef __LIGHT_SYSTEM_TASK__
#define __LIGHT_SYSTEM_TASK__

#include "components/led/Led.h"
#include "tasks/Task.h"

class LightSystemTask : public Task {
   public:
    LightSystemTask();
    void tick();

   private:
    Led* led1;
    Led* led2;
    Led* led3;
    Led* led4;
    enum { IDLE,
           ONGOING } state;
};

#endif