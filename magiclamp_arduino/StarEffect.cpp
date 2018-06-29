#include "Graph.h"
#include "StarEffect.h"
#include "Const.h"
#include "Arduino.h"
#include <FastLED.h>

StarEffect::StarEffect(CRGB *leds) {
	_leds = leds;
}

void StarEffect::update() {
 if (nextUpdate < millis()) {
    leds[random(NUM_LEDS-1)] = CRGB::White;
    nextUpdate = millis() + random(1000);
  }
  
  for (int i=0; i<NUM_LEDS; i++) {
   leds[i].fadeToBlackBy(1);
  }
  
  FastLED.show();  
}

void StarEffect::init() {}

