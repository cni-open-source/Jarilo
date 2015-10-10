//#define N_DEBUG
#include <MovingAvarageFilter.h>
#include "Jarilo_impl.h"


// utworzenie obiektu
// oraz przypisanie pinom fizycznych adresów
Jarilo j;


void setup()
{
  // konfiguracja obsługiwanych klawiszy
  j.configPinModes();

  // rozpoczęcie komunikacji przez port szeregowy,
  // a także z klawiaturą i myszą
  j.beginCommunication();
}


void loop() {
  // przetwarzanie sygnałów wejściowych
  j.process();

  // opóźnienie
  delay(25);
}

