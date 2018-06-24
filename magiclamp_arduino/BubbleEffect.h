/*
 * Bubbles.h
 *
 *  Created on: Jun 24, 2018
 *      Author: tf
 */

#ifndef BUBBLEEFFECT_H_
#define BUBBLEEFFECT_H_

#include "Effect.h"
#include <FastLED.h>

class BubbleEffect : public Effect {
public:
	BubbleEffect(int minSpeed, int maxSpeed, byte directions[], byte directionsLength);
	void update();
private:
	void updateBubble(int index);
};



#endif /* BUBBLEEFFECT_H_ */
