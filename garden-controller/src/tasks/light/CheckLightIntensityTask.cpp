#include "CheckLightIntensityTask.h"
#include "Config.h"

CheckLightIntensityTask::CheckLightIntensityTask() {
    this->lightSensor = new LightSensorImpl(PHOTORESISTOR_PIN);
}

void CheckLightIntensityTask::tick() {
    int lightIntensity = this->lightSensor->getLightIntensity();
}