/*
 * StarEffect.h
 *
 *  Created on: Jun 25, 2018
 *      Author: tf
 */

#ifndef STAREFFECT_H_
#define STAREFFECT_H_


#include "Effect.h"
#include <FastLED.h>

class StarEffect: public Effect {
public:
	StarEffect(CRGB *leds);
	virtual void update();
	virtual void init();
private:
	CRGB *_leds;
	unsigned long nextUpdate;
};


#endif /* STAREFFECT_H_ */
