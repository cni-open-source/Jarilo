//#define N_DEBUG
#include <MovingAvarageFilter.h>
#include "Jarilo_impl.h"

Jarilo j;

void setup()
{
  // przypisanie pinom fizycznych adresów
  // oraz konfiguracja obsługiwanych klawiszy
  j.assignPinValues();
  j.configPinModes();

  // rozpoczęcie komunikacji z klawiaturą
  // oraz przez port szeregowy
  j.beginCommunication();
}



void loop() {
  // przetwarzanie sygnałów wejściowych
  j.process();

  // opóźnienie 100 ms
  delay(100);
}

