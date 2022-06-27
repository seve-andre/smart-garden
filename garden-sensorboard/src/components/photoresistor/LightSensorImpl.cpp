#include "LightSensorImpl.h"

#include "Arduino.h"

LightSensorImpl::LightSensorImpl(int pin) {
    this->pin = pin;
}

int LightSensorImpl::getLightIntensity() {
    int value = analogRead(pin);
    return map(value, 0, 4095, 1, 8);
}