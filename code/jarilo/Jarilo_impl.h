#ifndef Jarilo_h
#define Jarilo_h

#include "Jarilo_priv.h"

class Jarilo : private JariloPriv
{
  public:
    Jarilo();
    void configPinModes();
    void beginCommunication();
    void process();

  private:
    void outputStrategy(Signal);
    void debugInfo(Signal);
    Signal m_signals[N_INPUTS];
};

#endif // Jarilo_h
