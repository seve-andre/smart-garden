#include "LightSystemTask.h"

#include "Config.h"
#include "Util.h"
#include "components/serial/MsgService.h"
#include "tasks/servo/IrrigationTask.h"

LightSystemTask::LightSystemTask(IrrigationTask* irrigationTask, MsgServiceBT* btMsgService) {
    this->led1 = new Led(LED_1_PIN);
    this->led2 = new Led(LED_2_PIN);
    this->led3 = new Led(LED_3_PWM_PIN);
    this->led4 = new Led(LED_4_PWM_PIN);

    this->irrigationTask = irrigationTask;
    this->btMsgService = btMsgService;
    this->state = AUTO;
}

void LightSystemTask::tick() {
    switch (state) {
        case AUTO: {
            if (MsgService.isMsgAvailable() && irrigationTask->state == IrrigationTask::State::IDLE) {
                Msg* msg = MsgService.receiveMsg();
                String msgContent = msg->getContent();

                Serial.println("content: " + msgContent);

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
                        this->irrigationTask->reset();
                        this->irrigationTask->state = IrrigationTask::State::ONGOING;
                    }
                } else {
                    this->led1->switchOff();
                    this->led2->switchOff();
                    this->led3->switchOff();
                    this->led4->switchOff();
                }

                /* NOT TO FORGET: msg deallocation */
                delete msg;
            } else if (this->irrigationTask->state == IrrigationTask::State::PAUSE) {
                this->led1->switchOff();
                this->led2->switchOff();
                this->led3->switchOff();
                this->led4->switchOff();
            }

            if (btMsgService->isMsgAvailable()) {
                Msg* msg = btMsgService->receiveMsg();
                String msgContent = msg->getContent();

                if (msgContent.equals("manual")) {
                    // manual
                    this->state = MANUAL;
                }

                delete msg;
            }
            break;
        }

        case MANUAL: {
            if (btMsgService->isMsgAvailable()) {
                Msg* msg = btMsgService->receiveMsg();
                String msgContent = msg->getContent();

                if (msgContent.equals("auto")) {
                    // auto
                    this->state = AUTO;
                } else if (msgContent.equals("L1")) {
                    // L1
                    if (this->led1->isOn()) {
                        this->led1->switchOff();
                    } else {
                        this->led1->switchOn();
                    }
                } else if (msgContent.equals("L2")) {
                    // L2
                    if (this->led2->isOn()) {
                        this->led2->switchOff();
                    } else {
                        this->led2->switchOn();
                    }
                } else if (msgContent.startsWith("3")) {
                    // 3in - n represents the value of the intensity (0-4)
                    int intensity = toDigit(msgContent[2]);
                    this->led3->turnOnWithIntensity(intensity);
                } else if (msgContent.startsWith("4")) {
                    // 4in
                    int intensity = toDigit(msgContent[2]);
                    this->led4->turnOnWithIntensity(intensity);
                } else if (msgContent.equals("irrigation")) {
                    // irrigation
                    // this->irrigationTask->state = PAUSE;
                } else if (msgContent.startsWith("s")) {
                    // sn - n represents the value of the speed (1-8)
                    int newSpeed = toDigit(msgContent[1]);
                    this->irrigationTask->speed = newSpeed;
                }

                delete msg;
            }
            break;
        }

        case ALARM: {
            if (btMsgService->isMsgAvailable()) {
                Msg* msg = btMsgService->receiveMsg();
                String msgContent = msg->getContent();

                if (msgContent.equals("alarm")) {
                    // alarm
                    this->state = AUTO;
                }

                delete msg;
            }
            break;
        }
    }
}