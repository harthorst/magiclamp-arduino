/*
 * Bubble.cpp
 *
 *  Created on: Jul 1, 2018
 *      Author: tf
 */

#include "Bubble.h"
#include "Graph.h"

Bubble::Bubble(int _actualPixel, byte _speed, byte _maxValue) {
	actualPixel = _actualPixel;
	speed = _speed;
	maxValue = _maxValue;
}

Bubble::Bubble() {}

bool Bubble::update() {
	actualValue = min(actualValue + speed, maxValue);
	lastValue = max(lastValue - (speed/2), 0);

	return actualValue == maxValue;
}




