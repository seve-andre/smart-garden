#ifndef __LED__
#define __LED__

#include "Light.h"

class Led : public Light {
   public:
    Led(int pin);
    void switchOn();
    void switchOff();
    bool isOn();
    void turnOnWithIntensity(int intensity);

   protected:
    int pin;
};

#endif
