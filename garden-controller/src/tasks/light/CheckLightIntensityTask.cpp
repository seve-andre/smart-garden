#include "CheckLightIntensityTask.h"

CheckLightIntensityTask::CheckLightIntensityTask() {
    this->lightSensor = new LightSensorImpl(1);
}

void CheckLightIntensityTask::tick() {
    int lightIntensity = this->lightSensor->getLightIntensity();
}