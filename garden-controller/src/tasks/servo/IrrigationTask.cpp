#include "IrrigationTask.h"

#include "Config.h"
#include "Util.h"
#include "components/serial/MsgService.h"
#include "components/servo/ServoMotorImpl.h"

IrrigationTask::IrrigationTask() {
    this->servo = new ServoMotorImpl(SERVO_PIN);
    this->state = IDLE;
    this->irrigationTime = 10000;
    this->speed = 1;
    this->pos = 0;
    this->servo->on();

    firstTimerInit = false;
    tStop = millis();
    tServo = millis();
    startServoTo180 = true;
    startServoTo0 = false;
    activeServo = false;
}

void IrrigationTask::tick() {
    switch (state) {
        case IDLE: {
            /* if (MsgService.isMsgAvailable()) {
                // wait for speed from sensors of the esp
                Msg* msg = MsgService.receiveMsg();
                String msgContent = msg->getContent();

                Serial.print(msgContent);

                int intensity = toDigit(msgContent[2]);
                int temperature = toDigit(msgContent[6]); */

            /* if the intensity is less than 2,
                the speed is set to the mapped temperature
                and the irrigation system starts to work
            */
            /* if (intensity < 2) {
                this->speed = temperature;
                state = ONGOING;
            }
        } */
            break;
        }
        case ONGOING: {
            // move servo with speed
            startServo();
            stopServo();
            timerServo();
            break;
        }
        case PAUSE: {
            // timer di 1 minuto; allo scadere impostare setActive(false)
            sleepIrrigation();
            break;
        }
        case COMPLETED: {
            break;
        }
    }
}

void IrrigationTask::startServo() {
    if (!firstTimerInit) {
        pos = 0;
        firstTimerInit = true;
    }

    if (startServoTo180) {
        moveServoTo180();
    }
}

void IrrigationTask::moveServoTo180() {
    if (pos < 180 && activeServo) {
        // tell servo to go to position in variable 'pos'
        activeServo = false;
        noInterrupts();
        pos += 3;
        interrupts();
        servo->setPosition(pos);
    } else if (pos == 180) {
        startServoTo180 = false;
        startServoTo0 = true;
    }
}

void IrrigationTask::moveServoTo0() {
    if (pos > 0 && activeServo) {
        // tell servo to go to position in variable 'pos'
        activeServo = false;
        noInterrupts();
        pos -= 3;
        interrupts();
        this->servo->setPosition(pos);
    } else if (pos == 0) {
        startServoTo180 = true;
        startServoTo0 = false;
    }
}

// Timer per fine rotazione a 180° di Servo
void IrrigationTask::stopServo() {
    // Interrupt
    if ((millis() - tStop) >= 15000) {
        servo->off();
        this->state = PAUSE;
        tStop = millis();
        tSleep = millis();
        Serial.println("Tempo Finito");
    }
}

void IrrigationTask::sleepIrrigation() {
    // Interrupt
    if ((millis() - tSleep) >= 60000) {
        // after staying asleep for 1 minute, goes back to getting intensity and temp values
        this->state = IDLE;
    }
}

// Timer per tick di Servo
void IrrigationTask::timerServo() {
    unsigned int servoSpeedTime = 0;
    switch (this->speed) {
        case 1:
            servoSpeedTime = 165;
            break;
        case 2:
            servoSpeedTime = 140;
            break;
        case 3:
            servoSpeedTime = 100;
            break;
        case 4:
            servoSpeedTime = 75;
            break;
        case 5:
            servoSpeedTime = 35;
            break;
    }

    // Interrupt
    if ((millis() - tServo) >= servoSpeedTime) {
        tServo = millis();
        activeServo = true;
    }
}

void IrrigationTask::reset() {
    tStop = millis();
    tServo = millis();
}