#include "LightSystemTask.h"

#include "Config.h"
#include "components/serial/MsgService.h"

LightSystemTask::LightSystemTask() {
    this->led1 = new Led(LED_1_PIN);
    this->led2 = new Led(LED_2_PIN);
    this->led3 = new Led(LED_3_PWM_PIN);
    this->led4 = new Led(LED_4_PWM_PIN);

    this->state = ONGOING;
}

void LightSystemTask::tick() {
    switch (state) {
        case IDLE: {
        }
        case ONGOING: {
            Msg* msg = MsgService.receiveMsg();
            String msgContent = msg->getContent();

            if (msgContent.startsWith("intensity")) {
                int intensity = msgContent.charAt(msgContent.length() - 1) - '0';

                this->led1->switchOn();
                this->led2->switchOn();

                // turn on based on intensity
                this->led3->turnOnWithIntensity(intensity);
                this->led4->turnOnWithIntensity(intensity);
            }
            break;
        }
    }
}
