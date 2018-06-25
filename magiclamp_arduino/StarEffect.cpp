
#ifdef star
void star() {
 if (nextUpdate < millis()) {
    leds[random(NUM_LEDS-1)] = CRGB::White;
    nextUpdate = millis() + random(1000);
  }
  
  for (int i=0; i<NUM_LEDS; i++) {
   leds[i].fadeToBlackBy(1);
  }
  
  FastLED.show();  
}
#endif
