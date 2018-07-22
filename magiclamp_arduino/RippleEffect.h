/*
 * StarEffect.h
 *
 *  Created on: Jun 25, 2018
 *      Author: tf
 */

#ifndef RIPPLEEFFECT_H_
#define RIPPLEEFFECT_H_


#include "Effect.h"
#include <FastLED.h>

class RippleEffect: public Effect {
public:
	RippleEffect(CRGB *leds);
	virtual void update();
	virtual void init();
private:
	CRGB *_leds;
	Graph graph;
	uint16_t speed = 2;
	uint16_t scale = 10;
	uint16_t y;
	uint16_t z;
};


#endif /* RIPPLEEFFECT_H_ */
