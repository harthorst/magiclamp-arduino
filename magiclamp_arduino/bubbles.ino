 

struct Bubble {
 int pixel = random(NUM_LEDS-1);
 int targetValue = random(50, 255);
 int speed = random(10, 50);
 CHSV color = CHSV(random(255), 255, 0);
};

#define NUM_BUBBLES 5

Bubble bubbleArr[NUM_BUBBLES];
int fade[NUM_LEDS];

void bubbles() {
  long time = millis();
  fadeToBlackBy(leds, NUM_LEDS, 10);
  Serial.print("black");
  Serial.println(millis()-time);
  
  time = millis();
  for (int i=0; i<NUM_BUBBLES; i++) {
   updateBubble(i);
  }
  Serial.print("bubbles");
  Serial.println(millis()-time);
  
  FastLED.show();
  
}

void updateBubble(int index) {
  Bubble *actual = &bubbleArr[index];  
  if (actual->color.value >= actual->targetValue) {
    int dir = random8(6);
    if (dir == 0) {
      dir = 7;
    } else if (dir == 1) {
      dir = 1;
    } else {
     dir = 0; 
    }
    fade[actual->pixel] = actual->speed;
    actual->pixel = getRel(actual->pixel, dir);
    actual->color.value = 0;
  } else {
    actual->color.value = min(actual->color.value + ((actual->targetValue * actual->speed) / 50), actual->targetValue);
  }
       
  leds[actual->pixel] = actual->color;
}

