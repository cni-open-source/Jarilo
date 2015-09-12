#ifndef JariloPriv_h
#define JariloPriv_h

#include <Arduino.h>
#include <MovingAvarageFilter.h>

class JariloPriv
{
  protected:
    struct Inputs {
      unsigned pin;
      unsigned key;
      MovingAvarageFilter filter;
      Inputs() : filter(20) {}
    };
    unsigned TRESHOLD = 20;
    static const unsigned N_INPUTS = 4;
    unsigned keys[N_INPUTS] = {KEY_UP_ARROW, KEY_DOWN_ARROW, KEY_LEFT_ARROW, KEY_RIGHT_ARROW};
    unsigned pins[N_INPUTS] = {A0, A1, A2, A3};
};

#endif // JariloPriv_h
