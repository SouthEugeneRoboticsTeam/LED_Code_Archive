#include "FastLED.h"
#define lct 58
#define DATA_PIN 9
#define PURPLE_HUE 200
#define redPinPin  4
#define bluePinPin 2
//blue HIGH, red HIGH: standBy //rainbows and purple
//blue LOW, red HIGH: seesCube //green
//blue HIGH, red LOW: hasCube //yellow
//blue LOW, blue LOW: timeAlert //flash red

CRGB leds[lct];
float p = lct + 6;
float r = lct + 6;
float t = 0;
float ps = 0;
boolean pu = false;
boolean bluePinVal = false;
boolean redPinVal = false;
void setup() {
  FastLED.addLeds<WS2812B, DATA_PIN, GRB>(leds, lct);
  pinMode(redPinPin, INPUT_PULLUP);
  pinMode(bluePinPin, INPUT_PULLUP);
  starta();
}
void loop() {
  readInputPins();
  if (bluePinVal == false && redPinVal == false) {
    standBy(); //rainbows and purple
  }
  if (bluePinVal == false && redPinVal == true) {
    seesCube(); //green
  }
  if (bluePinVal == true && redPinVal == false) {
    hasCube(); //purple
  }
  if (bluePinVal == true && redPinVal == true) {
    timeAlert(333, 7); //flash red
  }
}
void seesCube() {
  setAllLEDsRGB(200, 200, 0);
  FastLED.show();
}
void hasCube() {
  setAllLEDsRGB(155, 0, 155);
  FastLED.show();
}
void timeAlert(int d, int n) {
  for (int i = 0; i < n; i++) {
    setAllLEDsRGB(255, 0, 0);
    FastLED.show();
    delay(d / 2);
    setAllLEDsRGB(0, 0, 0);
    FastLED.show();
    delay(d / 2);
  }
}
void standBy() {
  for (int i = r; i < lct; i++) {
    ledHSV(i, map(int(i + lct + t + 210) % lct, 0, lct - 1, 0, 255), 255, 105);
  }
  if (ps < .6) {
    ps += .0004;
  }
  if (r > 0) {
    r -= ps;
  }
  t += .15;
  if (t <= 0) {
    t = lct;
  }
  if (pu == true) {
    p += ps;
    if (p > lct - 2) {
      pu = false;
    }
  } else {
    p -= ps;
    if (p <= 0) {
      pu = true;
    }
  }
  ledHSV(p, PURPLE_HUE, 255, 255);
  ledHSV(p + 1, PURPLE_HUE, 255, 210);
  ledHSV(p - 1, PURPLE_HUE, 255, 210);
  ledHSV(p + 2, PURPLE_HUE, 255, 180);
  ledHSV(p - 2, PURPLE_HUE, 255, 180);
  ledHSV(p + 3, PURPLE_HUE, 255, 150);
  ledHSV(p - 3, PURPLE_HUE, 255, 150);
  ledHSV(p + 4, PURPLE_HUE, 255, 130);
  ledHSV(p - 4, PURPLE_HUE, 255, 130);
  ledHSV(p + 5, PURPLE_HUE, 255, 100);
  ledHSV(p - 5, PURPLE_HUE, 255, 100);
  FastLED.show();
}

void starta() {
  for (int i = 0; i < lct + 2; i++) {
    ledHSV(i - 1, 210, 255, 100);
    for (int j = lct - 1; j > i - 7; j--) {
      ledHSV(j, 0, 0, 255);
      ledHSV(j + 1, 0, 0, 200);
      ledHSV(j + 2, 0, 0, 150);
      ledHSV(j + 3, 0, 0, 100);
      ledHSV(j + 4, 0, 0, 50);
      ledHSV(j + 5, 0, 0, 25);
      ledHSV(j + 6, 0, 0, 10);
      ledHSV(j + 7, 0, 0, 0);
      ledHSV(i - 1, PURPLE_HUE, 255, 100);
      ledHSV(i - 2, PURPLE_HUE, 255, 100);
      ledHSV(i - 3, PURPLE_HUE, 255, 100);
      ledHSV(i - 4, PURPLE_HUE, 255, 100);
      ledHSV(i - 5, PURPLE_HUE, 255, 100);
      ledHSV(i - 6, PURPLE_HUE, 255, 100);
      ledHSV(i - 7, PURPLE_HUE, 255, 100);
      ledHSV(i - 8, PURPLE_HUE, 255, 100);
      FastLED.show();
      delay(7);
    }
  }
  for (int i = 0; i < lct - 5; i++) {
    for (int j = i; j >= -6; j--) {
      ledHSV(j - 1, 0, 0, 255);
      ledHSV(j, 0, 0, 200);
      ledHSV(j + 1, 0, 0, 150);
      ledHSV(j + 2, 0, 0, 100);
      ledHSV(j + 3, 0, 0, 50);
      ledHSV(j + 4, 0, 0, 25);
      ledHSV(j + 5, 0, 0, 0);
      FastLED.show();
      delay(8);
    }
  }
}
void readInputPins() {
  if (digitalRead(redPinPin) == LOW) {
    redPinVal = false;
  }
  else {
    redPinVal = true;
  }
  if (digitalRead(bluePinPin) == LOW) {
    bluePinVal = false;
  }
  else {
    bluePinVal = true;
  }
}
void setAllLEDsHSV(int HUE, int SAT, int VAL) {
  for (int i = 0; i < lct; i++) {
    ledHSV(i, HUE, SAT, VAL);
  }
}
void ledHSV(int J, int HUE, int SAT, int VAL) {
  if (J >= 0 && J < lct) {
    leds[J] = CHSV(HUE, SAT, VAL);
  }
}
void setAllLEDsRGB(int R, int G, int B) {
  for (int i = 0; i < lct; i++) {
    ledRGB(i, R, G, B);
  }
}
void ledRGB(int J, int R, int G, int B) {
  if (J >= 0 && J < lct) {
    leds[J] = CRGB(R, G, B);
  }
}
