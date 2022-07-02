#include "LightSystemTask.h"

#include "Config.h"
#include "Util.h"
#include "components/serial/MsgService.h"
#include "tasks/servo/IrrigationTask.h"

LightSystemTask::LightSystemTask(IrrigationTask* irrigationTask) {
    this->led1 = new Led(LED_1_PIN);
    this->led2 = new Led(LED_2_PIN);
    this->led3 = new Led(LED_3_PWM_PIN);
    this->led4 = new Led(LED_4_PWM_PIN);

    this->irrigationTask = irrigationTask;
}

void LightSystemTask::tick() {
    if (MsgService.isMsgAvailable() && irrigationTask->state == IrrigationTask::State::IDLE) {
        Msg* msg = MsgService.receiveMsg();
        String msgContent = msg->getContent();

        // value 0-7
        int intensity = toDigit(msgContent[2]);
        int temperature = toDigit(msgContent[6]);

        if (intensity < 5) {
            this->led1->switchOn();
            this->led2->switchOn();

            // intensity value is already in range 0-4 when gets in here
            this->led3->turnOnWithIntensity(intensity);
            this->led4->turnOnWithIntensity(intensity);

            if (intensity < 2) {
                this->irrigationTask->speed = temperature;
                this->irrigationTask->state = IrrigationTask::State::ONGOING;
            }
        }

        /* NOT TO FORGET: msg deallocation */
        delete msg;
    } else if (this->irrigationTask->state == IrrigationTask::State::PAUSE) {
        this->led1->switchOff();
        this->led1->switchOff();
        this->led1->switchOff();
        this->led1->switchOff();
    }
}
