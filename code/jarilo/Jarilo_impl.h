#ifndef Jarilo_h
#define Jarilo_h

#include "Jarilo_priv.h"

class Jarilo : private JariloPriv
{
  public:
    Jarilo();
    void assignPinValues();
    void configPinModes();
    void beginCommunication();
    void process();

  private:
    Inputs m_input[N_INPUTS];
};

#endif // Jarilo_h
