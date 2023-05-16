#include <FastLED.h>

#define TAILLE 20
#define DELAYCLI 100
#define STARTDELAY 50
#define NUM_LEDS 20
#define PIN_LED 4


uint32_t orange = 0xF02E00;
uint32_t red = 0x100000;
uint32_t brightRed = 0xFF0000;
uint32_t startRed = 0xFF0000;

uint32_t black = 0x000000;
uint32_t reverseWhite = 0xCCCCCC;

void demarrage(CRGB* leds, CRGB* defaultState);
void freinage(bool value, CRGB* leds, CRGB* defaultState);
void recul(bool value, CRGB* leds, CRGB* defaultState);
void phares(bool value, CRGB* leds, CRGB* defaultState);
void clignooff(CRGB* leds, CRGB* defaultState, int * indexClignotant);
void clignodroite(CRGB* leds, CRGB* defaultState, int * indexClignotant, unsigned long * lastTimeCligno);
void clignogauche(CRGB* leds, CRGB* defaultState, int * indexClignotant, unsigned long * lastTimeCligno);
void warnings(CRGB* leds, CRGB* defaultState, int * indexClignotant, unsigned long * lastTimeCligno);
void arret(CRGB * leds);