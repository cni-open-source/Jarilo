#ifndef JariloPriv_h
#define JariloPriv_h

#include <Arduino.h>
#include <Keyboard.h>
#include <Mouse.h>
#include <MovingAvarageFilter.h>

namespace jarilo {

typedef byte AnalogInput;
typedef byte Action;
enum OutputDevice {KEYBOARD = 0, MOUSE = 1};

struct Signal
{
  private:
    MovingAvarageFilter filter;

  public:
    byte pin;
    byte value;
    bool outputType;
    bool hasTriggered;

    Signal(AnalogInput pin, Action value, OutputDevice Type)
      : filter(4)
      , pin(pin)
      , value(value)
      , outputType(outputType)
      , hasTriggered(false) {}
    uint16_t process(uint16_t reading) { return filter.process(reading); }
};

}

#endif // JariloPriv_h
