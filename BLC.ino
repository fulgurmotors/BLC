#include <FastLED.h>
#include "lights.h"

#define NUM_LEDS 20
#define PIN_LED 4

#define DELAYCLI 100
#define STARTDELAY 50
bool frein = 0;

int taille = NUM_LEDS / 4;
int indexClignotant = 0;

unsigned long lastTimeCligno = 0;


CRGB defaultState[NUM_LEDS];
CRGB leds[NUM_LEDS];

int brakes, reverse, DRL = 1, headlights, turnSignals, foglights;


void setup() {
  Serial1.begin(9600);
  FastLED.addLeds<WS2812, PIN_LED, GRB>(leds, NUM_LEDS);
  demarrage();

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

  freinage(brakes);
  recul(reverse);
  phares(headlights);


  switch(turnSignals){
    case 0: //clignotant droit
       clignooff();
       break;
     case 1: //clignotant droit
       clignodroite();
       break;
     case 2: //clignotant gauche
       clignogauche();
       break;
     case 3: //warnings
       warnings();
       break;
  }

  //arret();
}

void clignooff(){

  for (int i = taille - 1; i >= 0; i--){
    leds[i] = defaultState[i];
  }
  for (int i = NUM_LEDS - taille ; i < NUM_LEDS; i++){
    leds[i] = defaultState[i];
  }
    FastLED.show();
    indexClignotant = 0;
}

void clignodroite(){
  if(lastTimeCligno + DELAYCLI < millis()){

    int led = taille - indexClignotant - 1;
    leds[led].setColorCode(orange);

    indexClignotant++;

    if(indexClignotant == taille){
      indexClignotant = 0;
      for(int i = NUM_LEDS - taille - 1;i < taille;i++){
        leds[i] = defaultState[i];
      } 
    }

    FastLED.show();
    lastTimeCligno = millis();
  }
}

void clignogauche(){
  if(lastTimeCligno + DELAYCLI < millis()){

    int led = taille * 3 + indexClignotant;
    
    leds[led].setColorCode(orange);
    leds[(led - 2)%taille] = defaultState[(led - 1)%taille];
    FastLED.show();

    indexClignotant++;
    indexClignotant = indexClignotant % taille;
    lastTimeCligno = millis();
  }
}

void warnings(){
  
  if(lastTimeCligno + DELAYCLI < millis()){
  
    int led = taille - indexClignotant - 1;
    
    leds[led].setColorCode(orange);
    leds[(led - 2)%taille] = defaultState[(led - 2)%taille];

    led = taille * 3 + indexClignotant;
    
    leds[led].setColorCode(orange);
    leds[(led - 2)%taille] = defaultState[(led - 2)%taille];
    FastLED.show();

    indexClignotant++;
    indexClignotant = indexClignotant % taille;
    lastTimeCligno = millis();
  }
}

void demarrage(){
  for (int i = 0; i <= NUM_LEDS/2; i++){
    delay(STARTDELAY);
    leds[NUM_LEDS/2 - i - 1].setColorCode(startRed);
    leds[NUM_LEDS/2 + i].setColorCode(startRed);

    if(i != 0){
      leds[NUM_LEDS/2 - i].setColorCode(black);
      leds[NUM_LEDS/2 + i - 1].setColorCode(black);
    }
    FastLED.show();
  }

  for (int i = 0; i <= NUM_LEDS/2; i++){
    delay(STARTDELAY);

    leds[i].setColorCode(startRed);
    if(i-1 >= 0) leds[i-1].setColorCode(black);

    leds[NUM_LEDS - i - 1].setColorCode(startRed);
    if(i >= 1) leds[NUM_LEDS - i].setColorCode(black);
    FastLED.show();
  }

  for (int i = 0; i <= NUM_LEDS/2; i++){
    delay(STARTDELAY);

    leds[NUM_LEDS/2 - i - 1].setColorCode(startRed);
    leds[NUM_LEDS/2 + i].setColorCode(startRed);
    FastLED.show();
  }

  delay(3000);

  for (int i = 0; i < NUM_LEDS; i++){
    leds[i] = defaultState[i];
  }
  FastLED.show();
}

void freinage(bool value){
  for (int i = taille + 1; i < NUM_LEDS - taille - 1; i++){
    if(value)leds[i].setColorCode(brightRed);
    else leds[i] = defaultState[i];
  }
  FastLED.show();
}

void recul(bool value){
  if(value){
    leds[taille].setColorCode(reverseWhite);
    leds[NUM_LEDS - taille - 1].setColorCode(reverseWhite);    
  }
  else{
    leds[taille] = defaultState[taille];
    leds[NUM_LEDS - taille - 1] = defaultState[NUM_LEDS - taille - 1];       
  }
  FastLED.show();
}

void phares(bool value){
  for (int i = 0; i < NUM_LEDS; i++){
    if(value)defaultState[i].setColorCode(red);
    else defaultState[i].setColorCode(black);
    leds[i] = defaultState[i];
  }
  FastLED.show();
}

void arret(){
  for (int i = 0; i <= NUM_LEDS/2; i++){
    leds[NUM_LEDS/2 - i - 1].setColorCode(red);
    leds[NUM_LEDS/2 + i].setColorCode(red);

    if(i != 0){
      leds[NUM_LEDS/2 - i].setColorCode(black);
      leds[NUM_LEDS/2 + i - 1].setColorCode(black);
    }
    FastLED.show();
  }

  for (int i = 0; i <= NUM_LEDS/2; i++){
    leds[i].setColorCode(red);
    leds[NUM_LEDS - i - 1].setColorCode(red);
    FastLED.show();
  }

  for (int i = 0; i <= NUM_LEDS/2; i++){
    leds[NUM_LEDS/2 - i - 1].setColorCode(black);
    leds[NUM_LEDS/2 + i].setColorCode(black);
    FastLED.show();
  }
}