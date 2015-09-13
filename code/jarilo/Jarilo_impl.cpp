#include "Jarilo_impl.h"


Jarilo::Jarilo()
{
}


void Jarilo::assignPinValues()
{
  for (unsigned i = 0; i < N_INPUTS; ++i) {
    m_input[i].pin = pins[i];
    m_input[i].key = keys[i];
  }
}


void Jarilo::configPinModes()
{
  // ustawienie diody
  pinMode(LED_BUILTIN, OUTPUT);

  for (unsigned i = 0; i < N_INPUTS; ++i) {
    pinMode(m_input[i].pin, INPUT);
  }
  //digitalWrite(input_1, LOW); // obnizenie progu dla mniejszych szumów
}


void Jarilo::beginCommunication()
{
  // uruchomienie połączenia szeregowego
  Serial.begin(9600);

  // uruhomienie połączenia klawiatury
  Keyboard.begin();
}


void Jarilo::process()
{
  float reading, filtered;

  for (unsigned i = 0; i < N_INPUTS; ++i) {
    reading = analogRead(m_input[i].pin);
    filtered = m_input[i].filter.process(reading);

    if (filtered >= TRESHOLD) {
      digitalWrite(LED_BUILTIN, LOW);
    } else {
      digitalWrite(LED_BUILTIN, HIGH);
      Serial.println(m_input[i].key);
#ifdef N_DEBUG
      //Keyboard.begin();
      Keyboard.print(m_input[i].key);
      //Keyboard.end();
#endif
    }
  }
}

