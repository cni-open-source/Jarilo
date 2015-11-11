#include "Jarilo_impl.h"


Jarilo::Jarilo(jarilo::Signal* signals,
  const byte nInputs,
  const uint16_t treshold)
  : m_signals(signals)
  , TRESHOLD(treshold)
  , N_INPUTS(nInputs)
{
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
      debugInfo(m_signals[i]);
      if (false == m_signals[i].hasTriggered) {
        outputStrategy(m_signals[i]);
        m_signals[i].hasTriggered = true;
      }
    }
  }
  Serial.println();
}


void Jarilo::outputStrategy(jarilo::Signal s)
{
  switch(s.outputType) {
    case jarilo::KEYBOARD: {
      Keyboard.write(s.value);
      break;
    }
    case jarilo::MOUSE: {
      Mouse.click(s.value);
      break;
    }
    default: {}
  }
}


void Jarilo::debugInfo(jarilo::Signal s)
{
#ifndef N_DEBUG
  switch(s.value) {
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
}

