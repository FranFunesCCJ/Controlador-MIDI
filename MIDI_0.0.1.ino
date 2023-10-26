#include <MIDI.h>




MIDI_CREATE_DEFAULT_INSTANCE();                                               //Codigo generador generador de controlador
int potenciometros [4] = {A0, A1, A2, A3};
int analogValue [4] ={0, 0, 0, 0};
int lastAnalogValue [4] = {0, 0, 0, 0};
int cc[4] = {1, 2, 3, 4};


int botones [] = {2, 3, 4};
int notes [] = {60, 61, 62};
int canal = 1;
const int numBotones = sizeof(botones) / sizeof(botones[0]);
bool buttonState[numBotones] = {false};


void setup() {
  for (int i = 0; i < 3; i++) {                                               //Array para los botones INPUT_PULLUP
    pinMode(botones[i], INPUT_PULLUP);
  }
  Serial.begin(115200);                                                       //Uso 115200 ya que uso un puerto virtual MIDI

}

void loop() {
for (int i = 0; i < 5; i++) {
    analogValue[i] = analogRead(potenciometros[i]) / 8;

    if (analogValue[i] != lastAnalogValue[i]) {
      MIDI.sendControlChange(cc[i], analogValue[i], 1);
      lastAnalogValue[i] = analogValue[i];
    }
  }

{
  
  for (int i = 0; i < numBotones; i++) {
    bool currentState = digitalRead(botones[i]) == LOW;

    
    if (currentState != buttonState[i]) {
      buttonState[i] = currentState;

      if (currentState) {
        MIDI.sendNoteOn(notes[i], 127, canal);
      } else {
        MIDI.sendNoteOff(notes[i], 0, canal);
      }
    }
  }  }
}

