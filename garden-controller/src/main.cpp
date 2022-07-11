#include <Arduino.h>

#include "Config.h"
#include "components/bt/MsgServiceBT.h"
#include "components/serial/MsgService.h"
#include "tasks/Scheduler.h"
#include "tasks/Task.h"
#include "tasks/light/LightSystemTask.h"
#include "tasks/servo/IrrigationTask.h"

Scheduler scheduler;
MsgServiceBT *btMsgService;

void setup() {
    // initializes serial messagging service
    MsgService.init();

    // initializes bluetooth messagging service
    btMsgService = new MsgServiceBT(BT_TXD_PIN, BT_RXD_PIN);
    btMsgService->init();

    scheduler.init(10);

    Task *irrigationTask = new IrrigationTask();
    irrigationTask->init(40);

    Task *lightSystemTask = new LightSystemTask((IrrigationTask *)irrigationTask, btMsgService);
    lightSystemTask->init(40);

    scheduler.addTask(irrigationTask);
    scheduler.addTask(lightSystemTask);
}

void loop() {
    scheduler.schedule();
}
