//led code for Aluminati --updated 11/26/2017
#include "FastLED.h"
#define PIN 4 //led pin
#define lct 10//number of leds in strip
CRGB leds[lct];
unsigned long s = 0;
void setup() {
  FastLED.addLeds<NEOPIXEL, PIN>(leds, lct);
  for (int i = 0; i < lct; i++) {
    leds[i] = CRGB(0, 0, 0);
  }
  for (int i = 0; i <= lct / 2; i++) {
    for (int j = lct / 2; j > i; j--) {
      leds[j + 1] = CRGB(0, 0, 0);
      leds[j] = CRGB(255, 255, 220);
      for (int i = 0; i <= lct / 2; i++) {
        leds[lct - i - 1] = leds[i];
      }
      FastLED.show();
      delay(map(i, 0, lct / 2, 5, 30));
    }
    leds[i + 1] = CRGB(0, 0, 0);
    leds[i] = CHSV(200, 255, 170);
    for (int i = 0; i <= lct / 2; i++) {
      leds[lct - i - 1] = leds[i];
    }
    FastLED.show();
    delay(20);
  }
}
void loop() {
  for (int i = 0; i < lct; i++) {
    leds[i] = CRGB(0, 0, 0);
  }
  for (int i = 0; i <= lct / 2; i++) {
    s = (millis() / 15 + i * 256 / (lct / 2)) % (256 * 2);
    if (s > 255) {
      leds[(lct / 2) - i] = CHSV(200, 255, ((cos(((s - 127) % 256) * TWO_PI / 127) / 2) + .5) * 200 + 50);
    } else {
      leds[lct / 2 - i] = CHSV((s + 200) % 256, 255, 255);
    }
  }
  for (int i = 0; i <= lct / 2; i++) {
    leds[lct - i - 1] = leds[i];
  }
  FastLED.show();
  delay(1);
}
