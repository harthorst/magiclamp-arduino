
#ifdef life
boolean initialized = false;

void life() {
  if (!initialized) {
    leds[random(NUM_LEDS)] = CRGB::White;    
    leds[random(NUM_LEDS)] = CRGB::Red;
    leds[random(NUM_LEDS)] = CRGB::Blue;
    leds[random(NUM_LEDS)] = CRGB::Green;
    Serial.println(random(NUM_LEDS));
  }
  
  FastLED.show();
}

#endif
