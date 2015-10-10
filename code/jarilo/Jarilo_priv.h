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
      Signal(byte pin, byte value, bool outputType)
        : filter(4)
        , pin(pin)
        , value(value)
        , outputType(outputType)
        , hasTriggered(false) {}
      uint16_t process(uint16_t reading) { return filter.process(reading); }
    };
    const uint16_t TRESHOLD = 350;
    static const byte N_INPUTS = 6;
    enum {KEYBOARD = 0, MOUSE = 1};
};

#endif // JariloPriv_h
