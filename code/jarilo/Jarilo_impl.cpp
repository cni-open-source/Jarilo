#include "Jarilo_impl.h"


Jarilo::Jarilo()
{
}


void Jarilo::assignPinValues()
{
  for (byte i = 0; i < N_INPUTS; ++i) {
    m_signals[i].pin = pins[i];
    m_signals[i].value = values[i];
    m_signals[i].outputType = outputTypes[i];
  }
}


void Jarilo::configPinModes()
{
  // ustawienie diody
  pinMode(LED_BUILTIN, OUTPUT);

  for (byte i = 0; i < N_INPUTS; ++i) {
    pinMode(m_signals[i].pin, INPUT);
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
  uint16_t reading;

  for (byte i = 0; i < N_INPUTS; ++i) {
    reading = analogRead(m_signals[i].pin);
    reading = m_signals[i].process(reading);
    Serial.print(reading);
    Serial.print("\t: ");

    if (reading >= TRESHOLD) {
      digitalWrite(LED_BUILTIN, LOW);
      m_signals[i].hasTriggered = false;
    } else {
      digitalWrite(LED_BUILTIN, HIGH);
#ifndef N_DEBUG
      switch(m_signals[i].value) {
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
      if (false == m_signals[i].hasTriggered) {
        outputStrategy(m_signals[i]);
        m_signals[i].hasTriggered = true;
      }
    }
  }
  Serial.println();
}


void Jarilo::outputStrategy(Signal s)
{
  switch(s.outputType) {
    case KEYBOARD: {
      Keyboard.write(s.value);
      break;
    }
    case MOUSE: {
      Mouse.click(s.value);
      break;
    }
    default: {}
  }
}

