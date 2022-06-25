#include <Arduino.h>

#include "Config.h"
#include "GardenState.h"
#include "components/bt/MsgServiceBT.h"
#include "components/serial/MsgService.h"
#include "tasks/Scheduler.h"
#include "tasks/Task.h"
#include "tasks/light/LightSystemTask.h"
#include "tasks/servo/IrrigationTask.h"

Scheduler scheduler;
MsgServiceBT btMsgService(BT_RX_PIN, BT_TX_PIN);
uint8_t gardenState;

void setup() {
    // initializes serial messagging service
    MsgService.init();

    // initializes bluetooth messagging service
    btMsgService.init();

    scheduler.init(10);

    Task *irrigationTask = new IrrigationTask();
    irrigationTask->init(40);

    Task *lightSystemTask = new LightSystemTask();
    lightSystemTask->init(40);

    scheduler.addTask(irrigationTask);
    scheduler.addTask(lightSystemTask);

    // initially the state of the garden is set to AUTO
    gardenState = AUTO;
}

void loop() {
    switch (gardenState) {
        case AUTO:
            scheduler.schedule();
            break;
        case MANUAL:
            break;
        case ALARM:
            break;
    }
}
