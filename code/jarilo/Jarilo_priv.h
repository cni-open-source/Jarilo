#ifndef JariloPriv_h
#define JariloPriv_h

#include <Arduino.h>
#include <MovingAvarageFilter.h>

class JariloPriv
{
  protected:
    struct Inputs {
      MovingAvarageFilter filter;
      byte pin;
      byte value;
      bool hasTriggered;
      Inputs() : filter(4) {}
    };
    const uint16_t TRESHOLD = 200;
    static const byte N_INPUTS = 4;
    const byte pins[N_INPUTS] = {A0, A1, A2, A3};
    const byte values[N_INPUTS] = {
      KEY_LEFT_ARROW,
      KEY_UP_ARROW,
      KEY_RIGHT_ARROW,
      KEY_DOWN_ARROW
    };
};

#endif // JariloPriv_h
