/*
 * Bubble.h
 *
 *  Created on: Jul 1, 2018
 *      Author: tf
 */

#ifndef BUBBLE_H_
#define BUBBLE_H_
#include <FastLED.h>

class Bubble {
public:
	Bubble(int actualPixel, byte speed, byte maxValue);
	Bubble();
	/**
	 * returns true if actualValue reached maxValue
	 */
	bool update();

	int actualPixel;
	int lastPixel;
	byte speed;
	byte maxValue;
	byte actualValue;
	byte lastValue;
};

#endif /* BUBBLE_H_ */
