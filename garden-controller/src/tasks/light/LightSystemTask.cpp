#include "LightSystemTask.h"

#include "Config.h"
#include "Util.h"
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
            if (MsgService.isMsgAvailable()) {
                Msg* msg = MsgService.receiveMsg();
                String msgContent = msg->getContent();

                // value 0-7
                int intensity = toDigit(msgContent[2]);

                if (intensity < 5) {
                    this->led1->switchOn();
                    this->led2->switchOn();

                    // intensity value is already in range 0-4 when gets in here
                    this->led3->turnOnWithIntensity(intensity);
                    this->led4->turnOnWithIntensity(intensity);
                }
            }
            break;
        }
    }
}
