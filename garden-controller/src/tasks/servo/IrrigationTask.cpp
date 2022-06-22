#include "IrrigationTask.h"
#include "Config.h"
#include "components/servo/ServoMotorImpl.h"

IrrigationTask::IrrigationTask() {
    this->servo = new ServoMotorImpl(SERVO_PIN);
    this->state = ONGOING;
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

void IrrigationTask::setSpeed(int speed) {
    this->speed = speed;
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
        activeServo = false;  // tell servo to go to position in variable 'pos'
        noInterrupts();
        pos += 3;
        interrupts();
        servo->setPosition(pos);
        // delay(15);                                // waits 90ms for the servo
        // to reach the position
    } else if (pos >= 180) {
        startServoTo180 = false;
        startServoTo0 = true;
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
        this->state = ONGOING;
        this->setActive(false);
        Serial.println("i'm sleeping baby");
    }
}

// Timer per tick di Servo
void IrrigationTask::timerServo() {
    int servoSpeedTime = 0;
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

void IrrigationTask::resetStopTimer() {
    tStop = millis();
    tServo = millis();
}