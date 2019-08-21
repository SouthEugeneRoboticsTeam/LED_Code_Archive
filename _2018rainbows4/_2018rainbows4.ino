#include "FastLED.h"
#define lct 58
#define DATA_PIN 9
#define PURPLE_HUE 200
#define RED_HUE 0
#define BLUE_HUE 150
#define redAlliancePin  4//pull low to activate      pull high if disabled
#define blueAlliancePin 2//pull low to activate      pull high if disabled
unsigned long startMillis = 0;
boolean redAlliance = false;
boolean blueAlliance = false;
boolean matchStarted = false;
CRGB leds[lct];
float p = lct + 6;
float r = lct + 6;
float t = 0;
float ps = 0;
boolean pu = false;
void setup() {
  FastLED.addLeds<WS2812B, DATA_PIN, GRB>(leds, lct);
  pinMode(redAlliancePin, INPUT_PULLUP);
  pinMode(blueAlliancePin, INPUT_PULLUP);
  start();
  startMillis = millis();
}
void loop() {
  if (blueAlliance == false && redAlliance == false) {
    if (matchStarted) {
      postMatch();
    }
    else {
      prematch();
    }
    startMillis = millis();
  } else { //an alliance
    matchStarted = true;
    if (blueAlliance == true && redAlliance == true) {
      showAlert();
    }  else {
      if (blueAlliance == true) {
        showBlueAlliance();
      }
      if (redAlliance == true) {
        showRedAlliance();
      }
    }
  }
  readInputPins();
}
void showBlueAlliance() {
  if (millis() - startMillis < 15000) {
    blueAuto();
  }
  else if (millis() - startMillis >= 15000 && millis() - startMillis < 120000) {
    blueTele();
  }
  else if (millis() - startMillis >= 120000 && millis() - startMillis < 150000) {
    blueClimb();
  }
}
void showAlert() {
  for (int i = 0; i < lct; i++) {
    if (millis() % 150 < 100) {
      leds[i] = CRGB(255, 0, 255);
    }
    else {
      leds[i] = CRGB(170, 170, 170);
    }
  }
}
void blueAuto() {
  for (int i = 0; i < lct; i++) {
    leds[i] = CHSV(BLUE_HUE, 255, 128 * sin((millis() / 70 - i / 4)) + 127);
  }
  FastLED.show();
}
void blueTele() {
  for (int i = 0; i < lct; i++) {
    leds[i] = CHSV(BLUE_HUE, 255, 127);
  }
  FastLED.show();
}
void blueClimb() {
  for (int i = 0; i < lct; i++) {
    leds[i] = CHSV(BLUE_HUE, 255, 128 * sin((millis() / 70 - i / 4)) + 127);
  }
  FastLED.show();
}
void showRedAlliance() {
  if (millis() - startMillis < 15000) {
    redAuto();
  }
  else if (millis() - startMillis >= 15000 && millis() - startMillis < 120000) {
    redTele();
  }
  else if (millis() - startMillis >= 120000 && millis() - startMillis < 150000) {
    redClimb();
  }
}
void redAuto() {
  for (int i = 0; i < lct; i++) {
    leds[i] = CHSV(RED_HUE, 255, 128 * sin((millis() / 70 + i / 4)) + 127);
  }
  FastLED.show();
}
void redTele() {
  for (int i = 0; i < lct; i++) {
    leds[i] = CHSV(RED_HUE, 255, 127);
  }
  FastLED.show();
}
void redClimb() {
  for (int i = 0; i < lct; i++) {
    if ((i) - 3 * (i / 3) == int(millis() / map(millis() - startMillis, 120000, 150000, 600, 260)) - 3 * (int(millis() / map(millis() - startMillis, 120000, 150000, 600, 260)) / 3)) {
      leds[i] = CHSV(RED_HUE, 255, 255);
    } else {
      leds[i] = CHSV(PURPLE_HUE, 255, 90);
    }
  }
  FastLED.show();
}
void postMatch() {
  for (int i = 0; i < lct; i++) {
    unsigned long vTwFi = (i + millis() / 333) % 18;
    if (vTwFi == 1 || vTwFi == 2 || vTwFi == 4 || vTwFi == 5 || vTwFi == 6 || vTwFi == 7 || vTwFi == 8 || vTwFi == 10 || vTwFi == 11 || vTwFi == 13) {
      leds[i] = CRGB(255, 255, 250);
    } else {
      leds[i] = CHSV(PURPLE_HUE, 255, 120);
    }
  }
  FastLED.show();
}
void prematch() {
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
void start() {
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
      delay(8);
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
  if (digitalRead(redAlliancePin) == LOW) {
    redAlliance = false;
  }
  else {
    redAlliance = true;
  }
  if (digitalRead(blueAlliancePin) == LOW) {
    blueAlliance = false;
  }
  else {
    blueAlliance = true;
  }
}
void ledHSV(int J, int HUE, int SAT, int VAL) {
  if (J >= 0 && J < lct) {
    leds[J] = CHSV(HUE, SAT, VAL);
  }
}
