#include <Arduino.h>
#include "GardenState.h"
#include "components/serial/MsgService.h"
#include "tasks/Scheduler.h"
#include "tasks/Task.h"
#include "tasks/light/CheckLightIntensityTask.h"
#include "tasks/servo/IrrigationTask.h"
#include "tasks/temperature/CheckTemperatureTask.h"

Scheduler scheduler;

void setup() {
    // initializes serial messagging service
    MsgService.init();

    scheduler.init(10);

    Task* irrigationTask = new IrrigationTask();
    irrigationTask->init(40);
    irrigationTask->setActive(false);

    Task* checkTemperatureTask = new CheckTemperatureTask(irrigationTask);
    checkTemperatureTask->init(40);

    Task* checkLightIntensityTask = new CheckLightIntensityTask(irrigationTask);
    checkLightIntensityTask->init(40);

    scheduler.addTask(checkTemperatureTask);
    scheduler.addTask(checkLightIntensityTask);
    scheduler.addTask(irrigationTask);

    // initially the state of the garden is set to AUTO
    // gardenState = AUTO;
}

void loop() {
    /* switch (gardenState) {
        case AUTO:
            break;
        case MANUAL:
            break;
        case ALARM:
            break;
    } */
    scheduler.schedule();
}
