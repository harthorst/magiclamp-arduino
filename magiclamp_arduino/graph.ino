
#ifdef xxx
void testGetRel() {
  int actual = 11;
  
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
  
  myActual = actual;
  for (int i=0; i<5; i++) {
    myActual = getRel(myActual, 2);
    leds[myActual] = CRGB::Yellow;
  }
  
  myActual = actual;
  for (int i=0; i<5; i++) {
    myActual = getRel(myActual, 6);
    leds[myActual] = CRGB::Yellow;
  }
  
  FastLED.show();
}
#endif


//int relPos[NUM_LEDS][4] = {0};

void initGraph() {
  delay(2000);
  Serial.println(F("-"));
  Serial.println(F("-"));
  for (int i=0; i<NUM_LEDS; i++) {
    if (i!=0) {
      Serial.print(",");
    }
    Serial.print("{");
    for (byte k=0; k<8; k++) {
      if (k!=0) {
        Serial.print(",");
      }
      Serial.print(_getRel(i, k));
    }
    Serial.println("}");
  }
}

int getRel(int actual, byte dir) {
 return pgm_read_word(&REL_POS[actual][dir]);
}

int _getRel(int actual, byte dir) {
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
  } else if (dir==2) {
    ret = actual + COUNT_A + COUNT_B;
  } else if (dir==6) {
    ret = actual - (COUNT_A + COUNT_B);
  }
  
  if (ret<0) {
    ret = (NUM_LEDS) + ret;
  }
  
  return ret % NUM_LEDS;
}

