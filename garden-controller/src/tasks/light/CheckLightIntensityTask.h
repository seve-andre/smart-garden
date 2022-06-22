#ifndef __CHECK_LIGHT_INTENSITY_TASK__
#define __CHECK_LIGHT_INTENSITY_TASK__

#include "components/photoresistor/LightSensorImpl.h"
#include "tasks/Task.h"

class CheckLightIntensityTask : public Task {
   public:
    CheckLightIntensityTask();
    void tick();

   private:
    LightSensorImpl* lightSensor;
};

#endif