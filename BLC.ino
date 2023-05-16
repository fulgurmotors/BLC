#include "lights.h"

bool frein = 0;

int taille = NUM_LEDS / 4;
int indexClignotant = 0;

unsigned long lastTimeCligno = 0;


CRGB * defaultState;
CRGB * leds;

int brakes, reverse, DRL = 1, headlights, turnSignals, foglights;


void setup() {

  defaultState = (CRGB*)malloc(sizeof(CRGB) * NUM_LEDS);
  leds = (CRGB*)malloc(sizeof(CRGB) * NUM_LEDS);


  Serial1.begin(9600);
  FastLED.addLeds<WS2812, PIN_LED, GRB>(leds, NUM_LEDS);
  demarrage(leds, defaultState);

}

void loop() {
//Lumieres avant : position, croisement, route, brouillard, clignotant, warnings, diurnes
//Lumieres arrières : frein, recul, clignotant, warnings, phares, antibrouillard

  while(Serial1.available()){
    char inChar = Serial1.read();

    char type  = inChar >> 2;
    char value = inChar & B00000011;

    switch(type){
      case 1: //freins
        if(brakes != value){
          brakes = value;
        }
      break;
      case 2: //recul
        if(reverse != value){
          reverse = value;
        }
      break;
      case 3: //clignotant
        if(turnSignals != value){
          turnSignals = value;
        }
      break;
      case 4: //phares
        if(headlights != value){
          headlights = value;

        }
      break;
      case 5: //antibrouillard
        if(foglights != value){
          foglights = value;
        }
      break;
      
    }
  }

  freinage(brakes, leds, defaultState);
  recul(reverse, leds, defaultState);
  phares(headlights, leds, defaultState);


  switch(turnSignals){
    case 0: //clignotant droit
       clignooff(leds, defaultState, &indexClignotant);
       break;
     case 1: //clignotant droit
       clignodroite(leds, defaultState, &indexClignotant, &lastTimeCligno);
       break;
     case 2: //clignotant gauche
       clignogauche(leds, defaultState, &indexClignotant, &lastTimeCligno);
       break;
     case 3: //warnings
       warnings(leds, defaultState, &indexClignotant, &lastTimeCligno);
       break;
      default:
        clignooff(leds, defaultState, &indexClignotant);
        break;
  }

  //arret();
}