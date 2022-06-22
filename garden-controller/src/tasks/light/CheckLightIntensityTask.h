#ifndef __CHECK_LIGHT_INTENSITY_TASK__
#define __CHECK_LIGHT_INTENSITY_TASK__

#include "components/led/Led.h"
#include "components/photoresistor/LightSensor.h"
#include "tasks/Task.h"
#include "tasks/servo/IrrigationTask.h"

class CheckLightIntensityTask : public Task {
   public:
    CheckLightIntensityTask(IrrigationTask* irrTask);
    void tick();

   private:
    LightSensor* lightSensor;
    Led* led1;
    Led* led2;
    Led* led3;
    Led* led4;
    IrrigationTask* irrigationTask;
};

#endif