/*
 * Rainbow.h
 *
 *  Created on: Jun 24, 2018
 *      Author: tf
 */

#ifndef RAINBOWEFFECT_H_
#define RAINBOWEFFECT_H_

#include "Effect.h"
#include <FastLED.h>

class RainbowEffect: public Effect {
public:
	RainbowEffect(CRGB *leds);
	virtual void update();
	virtual void init();
private:
	CRGB *_leds;
};

#endif /* RAINBOWEFFECT_H_ */
