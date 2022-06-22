#include "IrrigationTask.h"
#include "Config.h"
#include "components/servo/ServoMotorImpl.h"

IrrigationTask::IrrigationTask() {
    this->servo = new ServoMotorImpl(SERVO_PIN);
    this->state = IDLE;
    this->irrigationTime = 10000;
    this->speed = 1;
}

void IrrigationTask::tick() {
    switch (state) {
        case IDLE: {
            break;
        }
        case ONGOING: {
            // move servo with speed
            break;
        }
        case PAUSE: {
            break;
        }
        case COMPLETED: {
            break;
        }
    }
}

void IrrigationTask::setSpeed(int speed) {
    this->speed = speed;
}