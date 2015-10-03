#include "Jarilo_impl.h"


Jarilo::Jarilo()
{
}


void Jarilo::assignPinValues()
{
  for (byte i = 0; i < N_INPUTS; ++i) {
    m_input[i].pin = pins[i];
    m_input[i].value = values[i];
    m_input[i].outputType = outputTypes[i];
  }
}


void Jarilo::configPinModes()
{
  // ustawienie diody
  pinMode(LED_BUILTIN, OUTPUT);

  for (byte i = 0; i < N_INPUTS; ++i) {
    pinMode(m_input[i].pin, INPUT);
  }
}


void Jarilo::beginCommunication()
{
  // uruchomienie połączenia szeregowego
  Serial.begin(9600);

  // uruchomienie połączenia klawiatury
  Keyboard.begin();

  // uruchomienie połączenia myszy
  Mouse.begin();
}


void Jarilo::process()
{
  float reading, filtered;

  for (byte i = 0; i < N_INPUTS; ++i) {
    reading = analogRead(m_input[i].pin);
    filtered = m_input[i].filter.process(reading);
    Serial.print(filtered);
    Serial.print("\t: ");

    if (uint16_t(filtered) >= TRESHOLD) {
      digitalWrite(LED_BUILTIN, LOW);
      m_input[i].hasTriggered = false;
    } else {
      digitalWrite(LED_BUILTIN, HIGH);
#ifndef N_DEBUG
      switch(m_input[i].value) {
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
#endif
      if (false == m_input[i].hasTriggered) {
        switch(m_input[i].outputType) {
          case KEYBOARD: {
            Keyboard.write(m_input[i].value);
            break;
          }
          case MOUSE: {
            Mouse.click(m_input[i].value);
            break;
          }
          default: {}
        }
        m_input[i].hasTriggered = true;
      }
    }
  }
  Serial.println();
}

