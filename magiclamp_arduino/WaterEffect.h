/*
 * StarEffect.h
 *
 *  Created on: Jun 25, 2018
 *      Author: tf
 */

#ifndef WATEREFFECT_H_
#define WATEREFFECT_H_


#include "Effect.h"
#include <FastLED.h>

class WaterEffect: public Effect {
public:
	WaterEffect(CRGB *leds);
	virtual void update();
	virtual void init();
private:
	CRGB *_leds;
	unsigned long nextUpdate;
};


#endif /* WATEREFFECT_H_ */
