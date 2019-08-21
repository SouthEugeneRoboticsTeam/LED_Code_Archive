#include "FastLED.h"
#define lightPin 10
#define buttonPin 5
#define buttonLightPin 13
#define knobPin A5
#define lct 240
CRGB leds[lct];
unsigned long firefliesArray[lct];
boolean traveling = false;
unsigned long travelMillis = 0;
float level = 0.000;
void setup() {
  pinMode(buttonPin, INPUT_PULLUP);
  pinMode(buttonLightPin, OUTPUT);
  pinMode(knobPin, INPUT);
  digitalWrite(buttonLightPin, HIGH);
  delay(150);
  digitalWrite(buttonLightPin, LOW);
  delay(150);
  digitalWrite(buttonLightPin, LOW);
  FastLED.addLeds<NEOPIXEL, lightPin>(leds, lct);
}
void loop() {
  if (digitalRead(buttonPin) == LOW) {
    if (traveling != true) {
      traveling = true;
      digitalWrite(buttonLightPin, HIGH);
      travelMillis = millis();
    }
  } else {
    if (traveling != false) {
      traveling = false;
      digitalWrite(buttonLightPin, LOW);
      travelMillis = millis();
    }
  }
  level = level * .8 + .2 * constrain(map(analogRead(knobPin), 375, 631, -35, lct - 1), -35, lct - 1);
  if (traveling) {
    for (int i = 0; i < lct; i++) {
      leds[i] = CHSV((200 - i * lct / 255) % 256, 255, constrain(map(level, 0, lct - 3, 255, 0), 0, 255));
    }
    firefliesDTHSOC(45, 500, 0, 255, false, true);
  } else {
    if (millis() - travelMillis < 1800) {
      firefliesDTHSOC(constrain(map(millis() - travelMillis, 0, 1300, 45, 0), 0, 45), 500, 0, 255, true, true);

    } else { //not traveling
      for (int i = 0; i < lct; i++) {
        if (i <= level) {
          leds[i] = CHSV(map(level - i + 200, 0, lct - 1, 0, 255) % 256, 255, 255);
        } else {
          leds[i] = CRGB(0, 0, 0);
        }
      }
      for (int i = level; i < level + 30; i++) {
        if (i >= 0 && i < lct) {
          leds[i] = CHSV(200, 255, map(i, level, level + 30, 255, 0));
        }
      }
    }
  }
  FastLED.show();
}
void firefliesDTHSOC(float d, int t, int h, int s, boolean o, boolean c) {
  for (int i = 0; i < lct; i++) {
    if (-firefliesArray[i] + millis() > t) {
      if (random(0, 1000) < d) {
        firefliesArray[random(0, lct - 1)] = millis();
      }
    }
  }
  for (int i = 0; i < lct; i++) {
    if (c == true) {
      h = firefliesArray[i] % 256;
    }
    if (-firefliesArray[i] + millis() <= t / 2 && -firefliesArray[i] + millis() > 0) {
      leds[i] = CHSV(h, s, map(millis() - firefliesArray[i], 0, t / 2, 0, 255));
    }
    if (-firefliesArray[i] + millis() > t / 2 && -firefliesArray[i] + millis() <= t) {
      leds[i] = CHSV(h, s, map(millis() - firefliesArray[i], t / 2, t, 255, 0));
    }
    if (-firefliesArray[i] + millis() > t && o == true) {
      leds[i] = CRGB(0, 0, 0);
    }
  }
}
