#ifndef __DEVICE_CONTROLLER__
#define __DEVICE_CONTROLLER__

class DeviceController{
 
public: 
  DeviceController(int pinPhotoresistance, int pinLed0, int pinLed1, int pinLed2, int pinLed3);
  unsigned int getValue();

private:
  int pinPhotoresistance;
  int pinLed0;
  int pinLed1;
  int pinLed2;
  int pinLed3;
};

#endif
