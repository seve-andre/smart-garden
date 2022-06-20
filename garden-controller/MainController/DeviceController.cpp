#include "DeviceController.h"
#include "Arduino.h"

DeviceController::DeviceController(int pinPhotoresistance, int pinLed0, int pinLed1, int pinLed2, int pinLed3) {
  this->pinPhotoresistance = pinPhotoresistance;
  this->pinLed0 = pinLed0;
  this->pinLed1 = pinLed1;
  this->pinLed2 = pinLed2;
  this->pinLed3 = pinLed3;
} 
  
unsigned int DeviceController::getValue(){
  float val = analogRead(pinPhotoresistance);
  return (unsigned int) map(val, 0, 1023, 0, 5);
}
