#include <Arduino.h>
#include "tasks/Scheduler.h"
#include "tasks/Task.h"
#include "tasks/temperature/CheckTemperatureTask.h"

Scheduler scheduler;

void setup() {
    scheduler.init(10);

    Task* checkTemperatureTask = new CheckTemperatureTask();
    checkTemperatureTask->init(40);

    scheduler.addTask(checkTemperatureTask);
}

void loop() {
    scheduler.schedule();
}