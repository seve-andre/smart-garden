#ifndef __CHECK_TEMPERATURE_TASK__
#define __CHECK_TEMPERATURE_TASK__

#include "components/temperature/TempSensorLM35.h"
#include "tasks/Task.h"

class CheckTemperatureTask : public Task {
   public:
    CheckTemperatureTask();
    void tick();

   private:
    TempSensorLM35* tempSensor;
};

#endif