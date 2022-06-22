#include <Arduino.h>
#include "tasks/Scheduler.h"
#include "tasks/Task.h"
#include "tasks/light/CheckLightIntensityTask.h"
#include "tasks/temperature/CheckTemperatureTask.h"

Scheduler scheduler;

void setup() {
    scheduler.init(10);

    Task* checkTemperatureTask = new CheckTemperatureTask();
    checkTemperatureTask->init(40);

    Task* checkLightIntensityTask = new CheckLightIntensityTask();
    checkTemperatureTask->init(40);

    scheduler.addTask(checkTemperatureTask);
    scheduler.addTask(checkLightIntensityTask);
}

void loop() {
    scheduler.schedule();
}