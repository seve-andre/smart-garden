#include "Led.h"

#include "Arduino.h"

int arduinoUnoPwmPins[] = {3, 5, 6, 9, 10, 11};

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
    bool exists = false;
    for (int p : arduinoUnoPwmPins) {
        if (p == pin) {
            exists = true;
            break;
        }
    }

    if (!exists) {
        Serial.println("You are not allowed to use turnOnWithIntensity method on a non-pwm pin.");
    }

    analogWrite(pin, map(intensity, 0, 4, 50, 255));
}
