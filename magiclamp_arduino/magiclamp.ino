#define FASTLED_ALLOW_INTERRUPTS 0

#include <FastLED.h>
#include "Arduino.h"
#include "Graph.h"
#include "Const.h"
#include "BubbleEffect.cpp"
#include "Effect.h"
#include "RainbowEffect.h"
#include "StarEffect.h"
#include "WaterEffect.h"
#include "ImageEffect.h"
#include "RippleEffect.h"

#define initblack
#define SERIAL_BUFFER_SIZE 8
#define debug
#define EFFECT_COUNT 8

unsigned long nextUpdate = 0;

CRGB leds[NUM_LEDS];

byte bubbleDir[] = { 7, 1, 0, 0, 0, 0 };
byte ffDir[] = { 0, 1, 2, 3, 4, 5, 6, 7 };
byte snakesDir[] = { 1, 3 };
BubbleEffect bubbles(leds, 10, 50, bubbleDir, 6);
BubbleEffect snakes(leds, 1, 10, snakesDir, 2);
BubbleEffect fireflies(leds, 1, 3, ffDir, 8);
RainbowEffect rainbow(leds);
StarEffect star(leds);
WaterEffect water(leds);
ImageEffect image(leds);
RippleEffect ripple(leds);

Effect* effects[EFFECT_COUNT];

volatile byte effectI = 0;

byte iterations = 0;
long nextDebug = 0;
int switchValue;
int8_t schrittTab[16] = { 0, -1, 1, 0, 1, 0, 0, -1, -1, 0, 0, 1, 0, 1, -1, 0 };
volatile int8_t altAB = 0;
long lastSwitchRotated = 0;
volatile int lastSwitchValue = 0;

void switchRotated() {
	int aVal = digitalRead(PIN_SWITCH_CLK);

	if (aVal == lastSwitchValue) {
		return;
	} else {
		lastSwitchValue = aVal;
	}

	boolean up = digitalRead(PIN_SWITCH_CLK) == digitalRead(PIN_SWITCH_DT);
	byte newEffectI = 0;
	if (up) {
		newEffectI = (effectI + 1) % EFFECT_COUNT;
	} else if (effectI == 0) {
		newEffectI = EFFECT_COUNT - 1;
	} else {
		newEffectI = effectI - 1;
	}
#ifdef debug
	Serial.print(digitalRead(PIN_SWITCH_CLK));
	Serial.print(" ");
	Serial.println(digitalRead(PIN_SWITCH_DT));
	Serial.print("setting effect to ");
	Serial.println(newEffectI);
#endif

	startEffect(newEffectI);
}

void switchPressed() {
#ifdef debug
	Serial.print("switch pressed");
	Serial.println(digitalRead(PIN_SWITCH_PRESS));
#endif
}

void setup() {
	pinMode(PIN_SWITCH_CLK, INPUT);
	pinMode(PIN_SWITCH_DT, INPUT);
	pinMode(PIN_SWITCH_PRESS, INPUT);

	attachInterrupt(digitalPinToInterrupt(PIN_SWITCH_CLK), switchRotated, CHANGE);
	attachInterrupt(digitalPinToInterrupt(PIN_SWITCH_PRESS), switchPressed, CHANGE);

	switchValue = digitalRead(PIN_SWITCH_CLK);

	//TIMSK0 = 1; // turn off timer0 for lower jitter

	FastLED.addLeds<NEOPIXEL, DATA_PIN>(leds, NUM_LEDS);
	//FastLED.setBrightness(255);
	//FastLED.setMaxPowerInVoltsAndMilliamps(5,100);

	effects[0] = &bubbles;
	effects[1] = &fireflies;
	effects[2] = &rainbow;
	effects[3] = &star;
	effects[4] = &water;
	effects[5] = &image;
	effects[6] = &ripple;
	effects[7] = &snakes;

#ifdef debug
	Serial.begin(9600);
#endif

	startEffect(1);
}

void loop() {
	//Serial.println(digitalRead(PIN_SWITCH_PRESS));

#ifdef debug
	if (millis() > nextDebug) {
		nextDebug = millis() + 1000;
		Serial.print(switchValue);
		Serial.print(" ");
		Serial.print(iterations);
		Serial.println(" fps");
		iterations = 0;
	} else {
		iterations++;
	}
#endif

	if (millis() > nextUpdate) {
		//startEffect((effectI + 1) % 3);
		nextUpdate = millis() + 20000;
	}
	effects[effectI]->update();
	//rainbow.update();
	//rainbow();
	//star();
}

void startEffect(int effect) {
	// TODO: destroy old effect
	effectI = effect;
	effects[effectI]->init();
}
