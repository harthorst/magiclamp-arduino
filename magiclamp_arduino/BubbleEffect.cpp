#include "Graph.h"
#include "BubbleEffect.h"
#include "Const.h"
#include "Arduino.h"
#include <FastLED.h>

Graph graph;
#define NUM_BUBBLES 5

CRGB leds[NUM_LEDS];

struct Bubble {
 int pixel = random(NUM_LEDS-1);
 int targetValue = random(50, 255);
 int speed;
 CHSV color = CHSV(random(255), 255, 0);
};


Bubble bubbleArr[NUM_BUBBLES];
int fade[NUM_LEDS];
byte *_directions;
byte _directionsLength;

BubbleEffect::BubbleEffect(int minSpeed, int maxSpeed, byte directions[], byte directionsLength) {
	_directions = directions;
	_directionsLength = directionsLength;

	FastLED.addLeds<NEOPIXEL, DATA_PIN>(leds, NUM_LEDS);
	FastLED.setBrightness( 255 );

	for (int i=0; i<NUM_BUBBLES; i++) {
		bubbleArr[i] = Bubble();
		bubbleArr[i].speed = random(minSpeed, maxSpeed);
		Serial.println(bubbleArr[i].speed);
	}
}

void Effect::init() {
}

void BubbleEffect::update() {
  long time = millis();
  fadeToBlackBy(leds, NUM_LEDS, 10);
  Serial.print("black");
  Serial.println(millis()-time);
  
  time = millis();
  for (int i=0; i<NUM_BUBBLES; i++) {
   this->updateBubble(i);
  }
  Serial.print("bubbles");
  Serial.println(millis()-time);
  
  FastLED.show();
  
}

void BubbleEffect::updateBubble(int index) {
  Bubble *actual = &bubbleArr[index];  
  if (actual->color.value >= actual->targetValue) {
	//byte directions[_directionsLength] = _directions;
    int dir = random8(_directionsLength);
    dir = _directions[dir];
    Serial.println(dir);
    fade[actual->pixel] = actual->speed;
    actual->pixel = graph.getRel(actual->pixel, dir);
    actual->color.value = 0;
  } else {
    actual->color.value = min(actual->color.value + ((actual->targetValue * actual->speed) / 50), actual->targetValue);
  }
       
  leds[actual->pixel] = actual->color;
}

