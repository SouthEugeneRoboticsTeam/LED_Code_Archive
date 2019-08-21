#include "FastLED.h"
#define TIME 8000
#define END_TIME 3000
#define TOP_LEDS 20//number of leds reserved for lighting the top

#define lightPin 10 //led pin
#define buttonPin 5
#define buttonLightPin 13
#define lct 240//number of leds in strip
CRGB leds[lct];
unsigned long t = 0;
boolean a = false;
int rs;
void setup() {
  pinMode(buttonPin, INPUT_PULLUP);
  pinMode(buttonLightPin, OUTPUT);
  digitalWrite(buttonLightPin, HIGH);
  delay(150);
  digitalWrite(buttonLightPin, LOW);
  delay(150);
  digitalWrite(buttonLightPin, HIGH);
  delay(150);
  digitalWrite(buttonLightPin, LOW);
  FastLED.addLeds<NEOPIXEL, lightPin>(leds, lct);
}
void loop() {
  if (digitalRead(buttonPin) == LOW && a == false) {//starting to time travel
    t = millis();
    a = true;
  }
  if (a == true) {// time traveling
    if (millis() % 200 >= 100) {//blink the button
      digitalWrite(buttonLightPin, HIGH);
    } else {
      digitalWrite(buttonLightPin, LOW);
    }
    for (int i = TOP_LEDS; i < lct; i++) {
      if (millis() - t <= TIME) {
        leds[i] = CHSV(0, 0, ((millis() - t)) % 256);
      } else {
        leds[i] = CHSV(0, 0, 255 - ((millis() - t) * 6 * 255 / END_TIME) % 256);
      }
    }
    if (millis() - t > TIME) {
      rs = random(-30, 30);
    }
    for (int i = 0; i <= (lct - TOP_LEDS); i++) {//animate lights
      if (millis() - t <= TIME) {
        if (map(millis() - t, 0, TIME, 0, lct - TOP_LEDS) >= i) {
          leds[i] = CHSV((((millis() - t) * 255 / TIME)), 255, 255);
        } else {
          leds[i] = CHSV(0, 0, 70);
        }
        if (i == (lct - TOP_LEDS) - ((millis() - t) / 10) % (lct - TOP_LEDS)) {
          leds[i] = CRGB(255, 255, 255);
        }
        if (i == 1.5*(lct - TOP_LEDS) - ((millis() - t) / 10) % (lct - TOP_LEDS)) {
          leds[i] = CRGB(255, 255, 255);
        }
        if (i == 1.25*(lct - TOP_LEDS) - ((millis() - t) / 10) % (lct - TOP_LEDS)) {
          leds[i] = CRGB(255, 255, 255);
        }
        if (i == 1.75*(lct - TOP_LEDS) - ((millis() - t) / 10) % (lct - TOP_LEDS)) {
          leds[i] = CRGB(255, 255, 255);
        }
      } else {
        leds[i] = CHSV(255, 255, constrain(map(millis() - t, TIME, TIME + END_TIME, 220, 0) + rs, 0, 255));
        if (random(0, lct) >= lct - 8) {
          leds[i] = CHSV(random(0, 255), 255, constrain(map(millis() - t, TIME, TIME + END_TIME, 255, 0), 0, 255));
        }
      }
    }
    if (millis() - t >= TIME + END_TIME) { //done time traveling
      a = 0;
    }
  } else {       //not time traveling
    digitalWrite(buttonLightPin, LOW);
    for (int i = 0; i < lct; i++) {
      leds[i] = CRGB(0, 0, 0);
    }
  }
  FastLED.show();
}
