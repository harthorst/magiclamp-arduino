/*
 * StarEffect.h
 *
 *  Created on: Jun 25, 2018
 *      Author: tf
 */

#ifndef IMAGEEFFECT_H_
#define IMAGEEFFECT_H_


#include "Effect.h"
#include <FastLED.h>
#include "Const.h"

class ImageEffect: public Effect {
public:
	ImageEffect(CRGB *leds);
	virtual void update();
	virtual void init();
private:
	CRGB *_leds;
	Graph graph;
	uint8_t scale = 1;
};


#endif
