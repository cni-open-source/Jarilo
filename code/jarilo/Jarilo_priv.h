#ifndef JariloPriv_h
#define JariloPriv_h

#include <Arduino.h>
#include <MovingAvarageFilter.h>

class JariloPriv
{
  protected:
    struct Signal {
      private: MovingAvarageFilter filter;
      public:
      byte pin;
      byte value;
      bool outputType;
      bool hasTriggered;
      Signal() : filter(4) {}
      uint16_t process(uint16_t reading) { return filter.process(reading); }
    };
    const uint16_t TRESHOLD = 350;
    static const byte N_INPUTS = 6;
    const byte pins[N_INPUTS] = {A0, A1, A2, A3, A4, A5};
    const byte values[N_INPUTS] = {
      KEY_LEFT_ARROW,
      KEY_UP_ARROW,
      KEY_RIGHT_ARROW,
      KEY_DOWN_ARROW,
      32, // 'spacebar'
      MOUSE_LEFT
    };
    enum {KEYBOARD = 0, MOUSE = 1};
    const byte outputTypes[N_INPUTS] = {0, 0, 0, 0, 0, 1};
};

#endif // JariloPriv_h
