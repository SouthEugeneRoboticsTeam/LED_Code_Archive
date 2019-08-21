#include "FastLED.h"
#define PIN 10 //led pin
#define lct 100//number of leds in strip
#define pin64 A3
#define pin32 A4
#define pin16 A5
#define pin8 A6
#define pin4 A7
#define pin2 3
#define pin1 2
#define enabledPin A0
#define autoPin A1
#define bluePin A2
CRGB leds[lct];
unsigned long firefliesArray[lct];
float firefliesDensity = 0;
int patternNum = 0;
float timeNum = 0.00000;
void setup() {
  FastLED.addLeds<NEOPIXEL, PIN>(leds, lct);
  pinMode(pin64, INPUT_PULLUP);
  pinMode(pin32, INPUT_PULLUP);
  pinMode(pin16, INPUT_PULLUP);
  pinMode(pin8, INPUT_PULLUP);
  pinMode(pin4, INPUT_PULLUP);
  pinMode(pin2, INPUT_PULLUP);
  pinMode(pin1, INPUT_PULLUP);
  pulseFlash();
  for (int i = 0; i < lct; i++) {
    firefliesArray[i] = 4294967294; //big and I mean it
  }
}
void loop() {
  if (digitalRead(enabledPin) == LOW) {//disabled
    if (patternNum == 0) {
      PATTERNFirefliesAndRainbows();
    }
    if (patternNum == 1) {
      PATTERNRainbowFireflies();
    }
    if (patternNum == 2) {
      PATTERNPulsing();
    }
    if (patternNum == 3) {
      allHSV(210, 255, 200);
      FastLED.show();
    }
  } else { //enabled
    timeRead();
    for (int n = 0; n < lct; n++) {
      if(n>lct*timeNum){
      int H = digitalRead(bluePin) == HIGH ? 170 : 200;
      int V = digitalRead(autoPin) == HIGH ? 10 : 255;
      leds[n] = CHSV(H, 255, V);
      }else{
      int H = digitalRead(bluePin) == HIGH ? 170 : 0;
      int V = digitalRead(autoPin) == HIGH ? 10 : 20;
      leds[n] = CHSV(H, 255, V);
      }
    }
    FastLED.show();
    firefliesDensity = 0;
    patternNum = millis() % 4; //num patterns random
  }
}
void timeRead() {
  timeNum = 0;
  if (digitalRead(pin64) == HIGH) {
    timeNum += 64;
  }
  if (digitalRead(pin32) == HIGH) {
    timeNum += 32;
  }
  if (digitalRead(pin16) == HIGH) {
    timeNum += 16;
  }
  if (digitalRead(pin8) == HIGH) {
    timeNum += 8;
  }
  if (digitalRead(pin4) == HIGH) {
    timeNum += 4;
  }
  if (digitalRead(pin2) == HIGH) {
    timeNum += 2;
  }
  if (digitalRead(pin1) == HIGH) {
    timeNum += 1;
  }
  timeNum=timeNum/255;
}
void PATTERNFirefliesAndRainbows() {
  if (firefliesDensity <= .005) {
    firefliesDensity += .000002;
  }
  wavesOfRainbowWSV(2, 10, 50);
  firefliesDTHSOC(firefliesDensity, 1500, 180, 145, false, false);
  FastLED.show();
}
void PATTERNRainbowFireflies() {
  firefliesDTHSOC(.05, 1500, 0, 200, true, true);
  FastLED.show();
}
void PATTERNPulsing() {
  pulseHSvVT(180, 255, 0, 255, 1000);
  FastLED.show();
}
void firefliesDTHSOC(float d, int t, int h, int s, boolean o, boolean c) {
  for (int i = 0; i < lct; i++) {
    if (-firefliesArray[i] + millis() > t) {
      if (random(0, 1000) < d * 1000.0000) {
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
void pulseFlash() {
  for (int b = 0; b <= 255; b += 1) {
    for (int i = 0; i <= 20; i++) {
      leds[i] = CHSV(180, map(b, 0, 255, 255, 145), map(i, 0, 20, b, 0));
    }
    for (int i = 0; i <= lct / 2; i++) {
      leds[lct - i - 1] = leds[i];
    }
    FastLED.show();
  }
  delay(500);
  for (int i = 0; i <= (lct / 2) + 10; i++) {
    if (i <= (lct / 2)) {
      leds[i] = CHSV(180, 145, 255);
    }
    if (i >= 10) {
      leds[i - 10] = CHSV(0, 0, 0);
    }
    for (int i = 0; i <= lct / 2; i++) {
      leds[lct - i - 1] = leds[i];
    }
    FastLED.show();
    delayMicroseconds(2000);
  }
  for (int v = 1; v <= 255; v += 20) {
    for (int i = 0; i <= lct; i++) {
      leds[i] = CHSV(180, 140, v);
    }
    FastLED.show();
    delayMicroseconds(255 / v);
  }
  for (int v = 255; v >= 0; v -= 5) {
    for (int i = 0; i <= lct; i++) {
      leds[i] = CHSV(180, map(v, 255, 0, 140, 255), v);
    }
    FastLED.show();
    delay(40);
  }
}
void pulseHSvVT(int H, int S, int v, int V, int T) {
  unsigned long milli = millis();
  if (milli % T < T / 2) {
    for (int i = 0; i < lct; i++) {
      leds[i] = CHSV(H, S, constrain(map(milli % T, 0, T / 2, v, V), v, V));
    }
  }
  if (milli % T >= T / 2) {
    for (int i = 0; i < lct; i++) {
      leds[i] = CHSV(H, S, constrain(map(milli % T, T / 2, T, V, v), v, V));
    }
  }
}
void wavesOfRainbowWSV(int wvs, int spd, int v) {
  for (int i = 0; i < lct; i++) {
    leds[i] = CHSV((i * wvs * 256 / lct + millis() / spd) % 256, 255, v);
  }
}
void allHSV(int H, int S, int V) {
  for (int i = 0; i < lct; i++) {
    leds[i] = CHSV(H, S, V);
  }
}
