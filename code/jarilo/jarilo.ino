//#define N_DEBUG
#include <MovingAvarageFilter.h>
#include "Jarilo_impl.h"

Jarilo j;

void setup()
{
  // inicjowanie i konfiguracja pinów wejściowych
  j.initPins();
  j.configPins();

  // rozpoczęcie komunikacji
  j.beginCommunication();
}



void loop() {
  // przetwarzanie sygnałów wejściowych
  j.process();

  // opóźnienie 100 ms
  delay(100);
}

