#include "Graph.h"
#include "WaterEffect.h"
#include "Const.h"
#include "Arduino.h"
#include <FastLED.h>

CRGB tmp[7];
Graph graph;
uint16_t speed = 5;
uint16_t scale = 1311;

static uint16_t x;
static uint16_t y;
static uint16_t z;

WaterEffect::WaterEffect(CRGB *leds) {
	_leds = leds;
}

void WaterEffect::update() {
	for (int i = 0; i < NUM_LEDS; i++) {

		uint8_t x = graph.getX(i);
		uint8_t y = graph.getY(i);

		int xoffset = scale * x;
		int yoffset = scale * y;

		uint8_t noise = inoise8(x + xoffset, y + yoffset, z);
		_leds[i] = CHSV(160,255,noise);
	}

	z += speed;

	FastLED.show();
}

void WaterEffect::init() {
	  x = random16();
	  y = random16();
	  z = random16();
}


