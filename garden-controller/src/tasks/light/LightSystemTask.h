#ifndef __LIGHT_SYSTEM_TASK__
#define __LIGHT_SYSTEM_TASK__

#include "components/bt/MsgServiceBT.h"
#include "components/led/Led.h"
#include "tasks/Task.h"
#include "tasks/servo/IrrigationTask.h"

class LightSystemTask : public Task {
   public:
    LightSystemTask(IrrigationTask* irrigationTask, MsgServiceBT* btMsgService);
    void tick();

   private:
    Led* led1;
    Led* led2;
    Led* led3;
    Led* led4;
    IrrigationTask* irrigationTask;
    MsgServiceBT* btMsgService;
    enum { AUTO,
           MANUAL,
           ALARM } state;
};

#endif