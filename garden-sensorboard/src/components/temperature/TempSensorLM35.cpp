#include "TempSensorLM35.h"

#include "Arduino.h"

#define VCC ((float)3.3)

TempSensorLM35::TempSensorLM35(int p) : pin(p) {}

float TempSensorLM35::getTemperature() {
    int value = analogRead(pin);
    float valueInVolt = value * VCC / 4096;
    float valueInCelsius = valueInVolt / 0.01;
    return valueInCelsius;
}
