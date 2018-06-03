#include <FastLED.h>
#define NUM_LEDS 261
#define DATA_PIN 6

#define COLUMNS 18
#define COUNT_A 15
#define COUNT_B 14
#define COUNT_AB 29

CRGB leds[NUM_LEDS];

unsigned long nextPixel = 0;
int actual = 11;

struct Pos {
  int x;
  int y;
} pos;

void setup() { 
       FastLED.addLeds<NEOPIXEL, DATA_PIN>(leds, NUM_LEDS);
       Serial.begin(9600);
}

void loop() {
  int myActual = actual;
  
  for (int i=0; i<5; i++) {
    myActual = getRel(myActual, 0);
    leds[myActual] = CRGB::White;
  }
  
  myActual = actual;
  for (int i=0; i<5; i++) {
    myActual = getRel(myActual, 4);
    leds[myActual] = CRGB::White;
  }
  
  myActual = actual;
  for (int i=0; i<5; i++) {
    myActual = getRel(myActual, 1);
    leds[myActual] = CRGB::Blue;
  }
  
  myActual = actual;
  for (int i=0; i<5; i++) {
    myActual = getRel(myActual, 3);
    leds[myActual] = CRGB::Red;
  }
  
  myActual = actual;
  for (int i=0; i<5; i++) {
    myActual = getRel(myActual, 5);
    leds[myActual] = CRGB::Blue;
  }
  
  myActual = actual;
  for (int i=0; i<5; i++) {
    myActual = getRel(myActual, 7);
    leds[myActual] = CRGB::Red;
  }
  
  FastLED.show();
  delay(100000);
}

int getRel(int actual, byte dir) {
  //boolean cont = true;
  boolean isA = true;
  int remainder = actual;
  while (true) {
     if ((isA && remainder <= COUNT_A-1) || (!isA && remainder <= COUNT_B-1)) {
       break;
     }
     if (isA) {
       remainder -= COUNT_A;
       isA = false;
     } else {
       remainder -= COUNT_B;
       isA = true;
     }
  }
  
  if (dir==0 || dir==1 || dir==7) {
    if (isA && remainder == 0) {
     remainder = COUNT_A -1;
     actual = actual + COUNT_A -1;
    }
  } else if (dir==3 || dir==4 || dir==5) {
    if (isA && remainder == COUNT_A-1) {
     remainder = 0;
     actual = actual - COUNT_A;
    }
  }
  
  Serial.print(remainder);
  Serial.print("-");
  Serial.println(isA);
  
  int ret = -1;
  
  if (dir==0) {
    if (isA) {
      ret = actual-1;
    } else {
      ret = actual+1;
    }
  } else if (dir==4) {
    if (isA) {
      ret = actual+1;
    } else {
      ret = actual-1;
    }
  } else if (dir==1) {
    if (isA) {
      ret = actual+COUNT_A+COUNT_B-(2*remainder);
    } else {
      ret = actual+(2*(COUNT_B-remainder))-1;
    }
  } else if (dir==3) {
    if (isA) {
      ret = actual+COUNT_A+COUNT_B-(2*remainder)-1;
    } else {
      ret = actual+(2*(COUNT_B-remainder));
    }
  } else if (dir==5) {
    if (isA) {
      ret = actual-((2*remainder)+1);
    } else {
      ret = actual-COUNT_A+COUNT_B-(2*remainder);
    }
  } else if (dir==7) {
    if (isA) {
      ret = actual-((2*remainder));
    } else {
      ret = actual-COUNT_A+COUNT_B-(2*remainder)-1;
    }
  }
  
  if (ret<0) {
    ret = (NUM_LEDS) + ret;
  }
  Serial.println(ret);
  
  return ret % NUM_LEDS;
}
    
int getLedPixel() {
  if (pos.x >= COLUMNS) {
    pos.x = COLUMNS-pos.x;
  }
  
  boolean isA = pos.x % 2 == 0;
  int maxY = isA ? COUNT_A : COUNT_B;
  
  if (pos.y >= maxY) {
   pos.y = maxY - pos.y;
  }
  
  int r = 0;
  
  //if (isA) {
  r = COUNT_AB * (pos.x / 2);
  
  if (!isA) {
    r += COUNT_A;
  }
  //} else {
  //  r = 
  //}
  
  return r;
}
    
void getPixelPos(int actual) {
  int div = actual / COUNT_AB;
  int mod = actual % COUNT_AB;
  boolean isA = false;
 
  pos = {div * 2, mod}; 
  
  if ((actual % COUNT_AB) < COUNT_A) {
    isA = true;
  } else {
    pos.x +=1;
    pos.y = COUNT_AB - (pos.y +1);
  }
  
  Serial.print(pos.x);
  Serial.print(" - ");
  Serial.println(pos.y);
}












