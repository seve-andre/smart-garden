#include "Led.h"

#include "Arduino.h"

Led::Led(int pin) {
    this->pin = pin;
    pinMode(pin, OUTPUT);
}

void Led::switchOn() {
    digitalWrite(pin, HIGH);
}

void Led::switchOff() {
    digitalWrite(pin, LOW);
}

void Led::turnOnWithIntensity(int intensity) {
    analogWrite(pin, map(intensity, 1, 5, 50, 255));
}
