#include "CheckTemperatureTask.h"
#include "Config.h"

CheckTemperatureTask::CheckTemperatureTask() {
    this->tempSensor = new TempSensorLM35(TEMP_SENSOR_PIN);
}

void CheckTemperatureTask::tick() {
    float temperature = this->tempSensor->getTemperature();
}