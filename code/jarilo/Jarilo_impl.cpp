#include "Jarilo_impl.h"


Jarilo::Jarilo()
  : m_signals({
              Signal(A0, KEY_LEFT_ARROW, KEYBOARD),
              Signal(A1, KEY_UP_ARROW, KEYBOARD),
              Signal(A2, KEY_RIGHT_ARROW, KEYBOARD),
              Signal(A3, KEY_DOWN_ARROW, KEYBOARD),
              Signal(A4, 32 /* space bar */, KEYBOARD),
              Signal(A5, MOUSE_LEFT, MOUSE)
              })
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


void Jarilo::debugInfo(Signal s)
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

