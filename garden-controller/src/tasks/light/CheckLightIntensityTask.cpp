#include "CheckLightIntensityTask.h"
#include "Config.h"
#include "components/photoresistor/LightSensorImpl.h"
#include "components/servo/ServoMotorImpl.h"

CheckLightIntensityTask::CheckLightIntensityTask(IrrigationTask* irrTask) {
    this->lightSensor = new LightSensorImpl(PHOTORESISTOR_PIN);
    this->led1 = new Led(CONTROLLER_LED_1);
    this->led2 = new Led(CONTROLLER_LED_2);
    this->led3 = new Led(CONTROLLER_LED_3);
    this->led4 = new Led(CONTROLLER_LED_4);
    this->irrigationTask = irrTask;
}

void CheckLightIntensityTask::tick() {
    int lightIntensity = this->lightSensor->getLightIntensity();

    if (lightIntensity < 5) {
        this->led1->switchOn();
        this->led2->switchOn();
    } else if (lightIntensity < 2) {
        // activate irrigation system
        // this->irrigationTask->activateIrrigation();
        this->irrigationTask->setActive(true);
    } else {
    }
}