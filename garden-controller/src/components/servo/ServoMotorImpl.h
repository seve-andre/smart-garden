#ifndef __SERVO_MOTOR_IMPL__
#define __SERVO_MOTOR_IMPL__

#include <arduino.h>
#include "ServoMotor.h"
#include "ServoTimer2.h"

class ServoMotorImpl : public ServoMotor {
   public:
    ServoMotorImpl(int pin);

    void on();
    void setPosition(int angle);
    void off();

   private:
    int pin;
    ServoTimer2 motor;
};

#endif
