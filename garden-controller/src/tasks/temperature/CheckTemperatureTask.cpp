#include "CheckTemperatureTask.h"

CheckTemperatureTask::CheckTemperatureTask() {
    this->tempSensor = new TempSensorLM35(0);
}

void CheckTemperatureTask::tick() {
    float temperature = this->tempSensor->getTemperature();
}