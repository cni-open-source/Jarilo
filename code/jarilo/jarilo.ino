#include <MovingAvarageFilter.h>
#include "Jarilo_impl.h"

#define TRESHOLD 20
#define N_INPUTS 4

void initPins(); // TODO: przenieść do klasy
void configPins(); // TODO: j.w.

// TODO: przenieść do nagłówka z konfiguracją
unsigned arrows[N_INPUTS] = {KEY_UP_ARROW, KEY_DOWN_ARROW, KEY_LEFT_ARROW, KEY_RIGHT_ARROW};
unsigned keys[N_INPUTS] = {A0, A1, A2, A3};

struct Inputs {
  unsigned pin;
  unsigned key;
  MovingAvarageFilter filter;
  Inputs() : filter(20) {}
};

Inputs input[2];

//Jarilo god;

void setup() {
  // ustawienie diody
  pinMode(LED_BUILTIN, OUTPUT);
  //god.init();

  // inicjowanie pinów wejściowych
  initPins();
  // konfiguracja pinów wejsciowych
  configPins();
  //digitalWrite(input_1, LOW); // obnizenie progu dla mniejszych szumów

  // uruchomienie połączenia szeregowego
  Serial.begin(9600);

  // uruhomienie połączenia klawiatury
  Keyboard.begin();
}



void loop() {

  float reading, filtered;

  for (unsigned i = 0; i < N_INPUTS; ++i) {
    reading = analogRead(input[i].pin);
    filtered = input[i].filter.process(reading);

    (filtered >= TRESHOLD)
      ? digitalWrite(LED_BUILTIN, LOW)
      : digitalWrite(LED_BUILTIN, HIGH);

    if (filtered >= TRESHOLD) {
      //Keyboard.begin();
      Keyboard.print(input[i].key);
      //Keyboard.end();
    }
  }

  delay(100);


  //float sensor_1;// = analogRead(input_1);
  //Serial.println(sensorVal);

  //float processed = maf_1.process(sensor_1);
  //Serial.print("1: ");
  //Serial.print(processed);

  //float sensor_2;// = analogRead(input_2);
  //processed = maf_2.process(sensor_2);
  //Serial.print(", 2: ");
  //Serial.println(processed);

  // Keep in mind the pullup means the pushbutton's
  // logic is inverted. It goes HIGH when it's open,
  // and LOW when it's pressed. Turn on pin 13 when the
  // button's pressed, and off when it's not:
  //(processed >= 20)
  //(processed >= 1000)
  //(processed > 10)
      //? digitalWrite(LED_BUILTIN, LOW)
      //: digitalWrite(LED_BUILTIN, HIGH);

  //delay(100);
}

void initPins()
{
  for (unsigned i = 0; i < N_INPUTS; ++i) {
    input[i].pin = keys[i];
    input[i].key = arrows[i];
  }
}


void configPins()
{
  for (unsigned i = 0; i < N_INPUTS; ++i) {
    pinMode(input[i].pin, INPUT);
  }
}

