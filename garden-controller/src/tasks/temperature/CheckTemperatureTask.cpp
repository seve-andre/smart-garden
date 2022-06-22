#include "CheckTemperatureTask.h"
#include "Arduino.h"
#include "Config.h"
#include "GardenState.h"

CheckTemperatureTask::CheckTemperatureTask(IrrigationTask* irrigationTask) {
    this->tempSensor = new TempSensorLM35(TEMP_SENSOR_PIN);
    this->irrigationTask = irrigationTask;
}

void CheckTemperatureTask::tick() {
    float temperature = this->tempSensor->getTemperature();
    int temperatureMapped = map(temperature, 0, 30, 1, 5);

    if (temperatureMapped == 5 &&
        this->irrigationTask->state == this->irrigationTask->State::PAUSE) {
        gardenState = ALARM;
    } else {
        this->irrigationTask->setSpeed(temperatureMapped);
    }
}
