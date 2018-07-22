/*
 * StarEffect.h
 *
 *  Created on: Jun 25, 2018
 *      Author: tf
 */

#ifndef WATEREFFECT_H_
#define WATEREFFECT_H_

#define NUM_BUBBLES 10

#include "Effect.h"
#include "Bubble.h"
#include <FastLED.h>

class WaterEffect: public Effect {
public:
	enum Mode {HUE = 0, SAT = 1, VAL = 2};

	WaterEffect(CRGB *leds);
	virtual void update();
	virtual void init();

	uint16_t hue = 160;
	uint16_t sat = 255;
	uint16_t val = 255;
	uint8_t threshold = 128;
	Mode mode = Mode::VAL;
private:
	CRGB *_leds;
	unsigned long nextUpdate;
	Graph graph;

	uint16_t speed = 5;
	uint16_t scale = 10;
	//uint16_t speed = 5;
	//uint16_t scale = 4011;
	uint16_t x;
	uint16_t y;
	uint16_t z;
	Bubble bubbles[NUM_BUBBLES];
};

#endif /* WATEREFFECT_H_ */
