#include "Graph.h"
#include "WaterEffect.h"
#include "Const.h"
#include "Arduino.h"
#include "Bubble.h"
#include <FastLED.h>

uint32_t nextMove = 0;

WaterEffect::WaterEffect(CRGB *leds) {
	_leds = leds;
}

void WaterEffect::update() {
	float factor = (float) 256 / threshold;
	//Serial.println(factor);

	for (int i = 0; i < NUM_LEDS; i++) {

		uint8_t x = graph.getX(i);
		uint8_t y = graph.getY(i);

		int xoffset = scale * x;
		int yoffset = scale * y;

		uint8_t noise = inoise8(x + xoffset, y + yoffset, z);

		if (mode == WaterEffect::Mode::VAL) {
			noise = max(0, noise - threshold) * factor;
			_leds[i] = CHSV(hue, sat, noise);
		} else if (mode == WaterEffect::Mode::HUE) {
			leds[i] = CHSV(noise, sat, val);
		} else {
			noise = max(0, noise - threshold) * factor;
			leds[i] = CHSV(hue, noise, val);
		}
	}

	z += speed;

	//_leds[bubble[0]] = CRGB::White;

	//bubble[0] = graph.getRel(bubble[0], DIR_U);

	bool updatePixels = false;
	if (millis() > nextMove) {
		nextMove = millis() + 10;
		//updatePixels = true;
	}

	for (int i = 0; i < NUM_BUBBLES; i++) {
		if (updatePixels) {
			bool next = bubbles[i].update();

			if (next) {
				bubbles[i].lastPixel = bubbles[i].actualPixel;
				bubbles[i].lastValue = bubbles[i].actualValue;
				bubbles[i].actualPixel = graph.getRel(bubbles[i].lastPixel,
				DIR_U);
				bubbles[i].actualValue = 0;
			}
		}
		/*
		leds[bubbles[i].lastPixel] = CHSV(128, 255, bubbles[i].lastValue);
		leds[bubbles[i].actualPixel] = CHSV(128, 255, bubbles[i].actualValue);
		*/
		leds[bubbles[i].lastPixel].addToRGB(bubbles[i].lastValue / 10);
		leds[bubbles[i].actualPixel].addToRGB(bubbles[i].actualValue / 10);

	}

	FastLED.show();
}

void WaterEffect::init() {
	x = random16();
	y = random16();
	z = random16();

	for (int i = 0; i < NUM_BUBBLES; i++) {
		bubbles[i].actualPixel = graph.getBottomLed(random8(COLUMNS));
		bubbles[i].speed = random8(1, 10);
		bubbles[i].maxValue = 100;
	}
}

