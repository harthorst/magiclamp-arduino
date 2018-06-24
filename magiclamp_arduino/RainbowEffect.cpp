#include "Graph.h"
#include "RainbowEffect.h"
#include "Const.h"
#include "Arduino.h"
#include <FastLED.h>

RainbowEffect::RainbowEffect() {
	FastLED.addLeds<NEOPIXEL, DATA_PIN>(leds, NUM_LEDS);
	FastLED.setBrightness( 255 );
}

void RainbowEffect::update() {
  int startHue = (millis() / 100) % 255;
  int hueDelta = 5;
  for (int i=0; i<COLUMNS / 2; i++) {
    fill_rainbow(&leds[i * (COUNT_A + COUNT_B)], COUNT_A, startHue , 5);
    fill_rainbow(&leds[i * (COUNT_A + COUNT_B) + COUNT_A], COUNT_B, startHue + (hueDelta * COUNT_B), -5);
  }
  FastLED.show();
}

