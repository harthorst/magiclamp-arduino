#include "Graph.h"
#include "RippleEffect.h"
#include "Const.h"
#include "Arduino.h"
#include <FastLED.h>


RippleEffect::RippleEffect(CRGB *leds) {
	_leds = leds;
}

void RippleEffect::update() {
	for (int i = 0; i < NUM_LEDS; i++) {;
		uint8_t y = graph.getY(i);

		int yoffset = scale * y;

		uint8_t noise = inoise8(y + yoffset, z);
		_leds[i] = CHSV(128,255,noise);
	}

	z += speed;

	FastLED.show();
}

void RippleEffect::init() {
	  y = random16();
	  z = random16();
}


