#include <FastLED.h>

#define NUM_LEDS 261
#define DATA_PIN 6

#define COLUMNS 18
#define COUNT_A 15
#define COUNT_B 14
#define COUNT_AB 29
#define initblack
#define SERIAL_BUFFER_SIZE 8

CRGB leds[NUM_LEDS];
unsigned long nextUpdate = 0;

void setup() { 
  //TIMSK0 = 1; // turn off timer0 for lower jitter
       
       randomSeed(analogRead(0));
       FastLED.addLeds<NEOPIXEL, DATA_PIN>(leds, NUM_LEDS);
       FastLED.setBrightness( 255 );
       Serial.begin(9600);
       //delay(2000000);
       
       //initGraph();
       testGetRel();
}

void loop() {
   //bubbles();
   //star();
}













