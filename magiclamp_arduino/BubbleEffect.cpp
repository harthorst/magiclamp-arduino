#ifndef BUBBLEEFFECT_CPP
#define BUBBLEEFFECT_CPP

#include "Graph.h"
#include "BubbleEffect.h"
#include "Const.h"
#include "Arduino.h"
#include "Effect.h"
#include <FastLED.h>

#define NUM_BUBBLES 5

class BubbleEffect: public Effect {
private:
	Graph graph;

	CRGB *leds;

	struct Bubble {
		int pixel = random(NUM_LEDS - 1);
		int targetValue = random(50, 255);
		int speed;
		CHSV color = CHSV(random(255), 255, 0);
	};

	Bubble bubbleArr[NUM_BUBBLES];
	byte *_directions;
	byte _directionsLength;

	void updateBubble(int index) {
		Bubble *actual = &bubbleArr[index];
		if (actual->color.value >= actual->targetValue) {
			int dir = random8(_directionsLength);
			dir = _directions[dir];
			actual->pixel = graph.getRel(actual->pixel, dir);
			actual->color.value = 0;
		} else {
			actual->color.value = min(
					actual->color.value
							+ ((actual->targetValue * actual->speed) / 100),
					actual->targetValue);
		}

		leds[actual->pixel] = actual->color;
	}

public:
	BubbleEffect(CRGB *_leds, int minSpeed, int maxSpeed, byte directions[],
			byte directionsLength) {
		_directions = directions;
		_directionsLength = directionsLength;
		leds = _leds;

#ifdef debug
		minSpeed *=2;
		maxSpeed *=2;
#endif

		for (int i = 0; i < NUM_BUBBLES; i++) {
			bubbleArr[i] = Bubble();
			bubbleArr[i].speed = random(minSpeed, maxSpeed);
		}
	}

	void init() {
	}

	void update() {
		long time = millis();
		fadeToBlackBy(leds, NUM_LEDS, 10);
#ifdef debug
		Serial.print("black");
		Serial.println(millis() - time);
#endif

		time = millis();
		for (int i = 0; i < NUM_BUBBLES; i++) {
			this->updateBubble(i);
		}
#ifdef debug
		Serial.print("bubbles");
		Serial.println(millis() - time);
#endif

		FastLED.show();

	}
};
#endif

