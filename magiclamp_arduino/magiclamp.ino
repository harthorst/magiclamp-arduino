#include <FastLED.h>
#include "Arduino.h"
#include "Graph.h"
#include "Const.h"
#include "BubbleEffect.h"
#include "RainbowEffect.h"





#define initblack
#define SERIAL_BUFFER_SIZE 8

unsigned long nextUpdate = 0;

byte bubbleDir[] = {7, 1, 0, 0, 0, 0};
byte ffDir[] = {0, 1, 2, 3, 4, 5, 6, 7};
//BubbleEffect bubbles(10, 50, bubbleDir, 6);
BubbleEffect fireflies(1, 5, ffDir, 8);
RainbowEffect rainbow;

void setup() {
  //TIMSK0 = 1; // turn off timer0 for lower jitter


       Serial.begin(9600);

       //initGraph();
       //testGetRel();
}

void loop() {

   //bubbles.update();
   fireflies.update();
	//rainbow.update();
   //rainbow();
   //star();
}
