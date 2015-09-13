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
    Serial.print(filtered);
    Serial.print("\t: ");

    if (filtered >= TRESHOLD) {
      digitalWrite(LED_BUILTIN, LOW);
    } else {
      digitalWrite(LED_BUILTIN, HIGH);
#ifndef N_DEBUG
      switch(m_input[i].key) {
        case KEY_UP_ARROW: {
          Serial.println("up");
          break;
        }
        case KEY_DOWN_ARROW: {
          Serial.println("down");
          break;
        }
        case KEY_LEFT_ARROW: {
          Serial.println("left");
          break;
        }
        case KEY_RIGHT_ARROW: {
          Serial.println("right");
          break;
        }
      }
#else
      //Keyboard.begin();
      Keyboard.write(m_input[i].key);
      //Keyboard.end();
#endif
    }
  }
  Serial.println();
}

