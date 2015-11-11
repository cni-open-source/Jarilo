#ifndef Jarilo_h
#define Jarilo_h

#include "Jarilo_priv.h"

class Jarilo
{
  public:
    Jarilo(jarilo::Signal* signals,
      const byte nInputs,
      const uint16_t treshold = 350);
    void configPinModes();
    void beginCommunication();
    void process();

  private:
    void outputStrategy(jarilo::Signal);
    void debugInfo(jarilo::Signal);

    jarilo::Signal* m_signals;
    const uint16_t TRESHOLD;
    const byte N_INPUTS;
};

#endif // Jarilo_h
