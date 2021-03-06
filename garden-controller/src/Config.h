#ifndef __CONFIG__
#define __CONFIG__

#define LED_1_PIN 3
#define LED_2_PIN 4

// led 3 and 4 must have PWM pins, since they use analogWrite, instead of digitalWrite
#define LED_3_PWM_PIN 5
#define LED_4_PWM_PIN 6

#define SERVO_PIN 9

#define BT_TXD_PIN 12
#define BT_RXD_PIN 13

#endif
