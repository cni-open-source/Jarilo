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
      bool hasClicked;
      Inputs() : filter(4) {}
    };
    const uint16_t TRESHOLD = 200;
    static const unsigned N_INPUTS = 4;
    const unsigned keys[N_INPUTS] = {KEY_UP_ARROW, KEY_DOWN_ARROW, KEY_LEFT_ARROW, KEY_RIGHT_ARROW};
    const unsigned pins[N_INPUTS] = {A0, A1, A2, A3};
};

#endif // JariloPriv_h
