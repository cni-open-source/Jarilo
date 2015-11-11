//#define N_DEBUG
#include <MovingAvarageFilter.h>
#include "Jarilo_impl.h"

using jarilo::Signal;

// przypisanie pinom fizycznych adresów
Signal signals[] = {
  Signal(A0, KEY_LEFT_ARROW, jarilo::KEYBOARD),
  Signal(A1, KEY_UP_ARROW, jarilo::KEYBOARD),
  Signal(A2, KEY_RIGHT_ARROW, jarilo::KEYBOARD),
  Signal(A3, KEY_DOWN_ARROW, jarilo::KEYBOARD),
  Signal(A4, 32 /* space bar */, jarilo::KEYBOARD),
  Signal(A5, MOUSE_LEFT, jarilo::MOUSE)
};

// utworzenie obiektu Jaryło
Jarilo j(signals, sizeof(signals) / sizeof(Signal));


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

