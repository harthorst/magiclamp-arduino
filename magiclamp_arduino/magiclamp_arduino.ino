#include <FastLED.h>
#define NUM_LEDS 261
#define DATA_PIN 6

#define COLUMNS 18
#define COUNT_A 15
#define COUNT_B 14
#define COUNT_AB 29

CRGB leds[NUM_LEDS];

long nextUpdate = 0;
int actual = random(NUM_LEDS-1);

void setup() { 
       FastLED.addLeds<NEOPIXEL, DATA_PIN>(leds, NUM_LEDS);
       Serial.begin(9600);
}

void loop() {
  if (nextUpdate<millis()) {
    int dir = random(4);
    if (dir == 0) {
      dir = 7;
    } else if (dir == 1) {
      dir = 1;
    } else {
     dir = 0; 
    }
    actual = getRel(actual, dir);
    leds[actual] = CRGB::White;
    nextUpdate = millis() + 50;
  }
  
  for (int i=0; i<NUM_LEDS; i++) {
   leds[i].fadeToBlackBy(10); 
  }
    
  
  FastLED.show();
}













