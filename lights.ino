#include "lights.h"

void clignooff(CRGB* leds, CRGB* defaultState, int * indexClignotant){

  for (int i = NUM_LEDS * TAILLE_CLIGNO - 1; i >= 0; i--){
    leds[i] = defaultState[i];
  }
  for (int i = NUM_LEDS * (1 - TAILLE_CLIGNO) ; i < NUM_LEDS; i++){
    leds[i] = defaultState[i];
  }
    FastLED.show();
    *indexClignotant = 0;
}

void clignodroite(CRGB* leds, CRGB* defaultState, int * indexClignotant, unsigned long * lastTimeCligno){
  if(*lastTimeCligno + DELAYCLI < millis()){

    int led = NUM_LEDS * TAILLE_CLIGNO - *indexClignotant - 1;
    leds[led].setColorCode(orange);

    indexClignotant++;

    if(*indexClignotant == NUM_LEDS * TAILLE_CLIGNO){
      *indexClignotant = 0;
      for(int i = 0;i < NUM_LEDS * TAILLE_CLIGNO;i++){
        leds[i] = defaultState[i];
      } 
    }

    FastLED.show();
    *lastTimeCligno = millis();
  }
}

void clignogauche(CRGB* leds, CRGB* defaultState, int * indexClignotant, unsigned long * lastTimeCligno){
  if(*lastTimeCligno + DELAYCLI < millis()){

    int led = NUM_LEDS * (1 - TAILLE_CLIGNO) - 1 + *indexClignotant;
    leds[led].setColorCode(orange);

    *indexClignotant++;

    if(*indexClignotant == NUM_LEDS * TAILLE_CLIGNO){
      *indexClignotant = 0;
      for(int i = NUM_LEDS * (1 - TAILLE_CLIGNO) - 1;i < NUM_LEDS;i++){
        leds[i] = defaultState[i];
      } 
    }

    FastLED.show();
    *lastTimeCligno = millis();
  }
}

void warnings(CRGB* leds, CRGB* defaultState, int * indexClignotant, unsigned long * lastTimeCligno){
  
  if(*lastTimeCligno + DELAYCLI < millis()){
  
    int led = NUM_LEDS * (1 - TAILLE_CLIGNO) - 1 + *indexClignotant;
    leds[led].setColorCode(orange);
    led = NUM_LEDS * TAILLE_CLIGNO - *indexClignotant - 1;
    leds[led].setColorCode(orange);

    *indexClignotant++;

    if(*indexClignotant == NUM_LEDS * TAILLE_CLIGNO){
      *indexClignotant = 0;
      for(int i = NUM_LEDS * (1 - TAILLE_CLIGNO) - 1;i < NUM_LEDS;i++){
        leds[i] = defaultState[i];
      }
      for(int i = 0;i < NUM_LEDS * TAILLE_CLIGNO;i++){
        leds[i] = defaultState[i];
      }
    }

    FastLED.show();
    *lastTimeCligno = millis();
  }
}

void demarrage(CRGB* leds, CRGB* defaultState){
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

void freinage(bool value, CRGB* leds, CRGB* defaultState){
  for (int i = NUM_LEDS * TAILLE_CLIGNO + 1; i < NUM_LEDS * (1 - TAILLE_CLIGNO) - 1; i++){
    if(value)leds[i].setColorCode(brightRed);
    else leds[i] = defaultState[i];
  }
  FastLED.show();
}

void recul(bool value, CRGB* leds, CRGB* defaultState){
  if(value){
    leds[(int)(NUM_LEDS * TAILLE_CLIGNO)].setColorCode(reverseWhite);
    leds[(int)(NUM_LEDS * (1 - TAILLE_CLIGNO) - 1)].setColorCode(reverseWhite);    
  }
  else{
    leds[(int)(NUM_LEDS * TAILLE_CLIGNO)] = defaultState[(int)(NUM_LEDS * TAILLE_CLIGNO)];
    leds[(int)(NUM_LEDS * (1 - TAILLE_CLIGNO) - 1)] = defaultState[(int)(NUM_LEDS  * (1 - TAILLE_CLIGNO) - 1)];       
  }
  FastLED.show();
}

void phares(bool value, CRGB* leds, CRGB* defaultState){
  for (int i = 0; i < NUM_LEDS; i++){
    if(value)defaultState[i].setColorCode(red);
    else defaultState[i].setColorCode(black);
    leds[i] = defaultState[i];
  }
  FastLED.show();
}

void arret(CRGB * leds){
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