#include "FastLED.h"
#define maxMode 5
#define lightPin 10 //led pin
#define buttonPin 5
#define buttonLightPin 13
#define lct 240//number of leds in strip
CRGB leds[lct];
unsigned long firefliesArray[lct];
boolean b = false; //was the button released (set false immediately)
int modeVal = 0;
unsigned long t = 0;
void setup() {
  pinMode(buttonPin, INPUT_PULLUP);
  pinMode(buttonLightPin, OUTPUT);
  digitalWrite(buttonLightPin, HIGH);
  delay(150);
  digitalWrite(buttonLightPin, LOW);
  delay(150);
  digitalWrite(buttonLightPin, HIGH);
  FastLED.addLeds<NEOPIXEL, lightPin>(leds, lct);
}
void loop() {
  buttonStuff();
  if (modeVal == 0) {
    allHSV(200, 255, 255);/////////if button triggered purple
  }
  if (modeVal == 1) {
    twoFiveTwoOneInLights();////////////////////////////////////////2 5 2 1 in lights
  }
  if (modeVal == 2) {
    twoFiveTwoOneInLightsB();////////////////////////////////////////2 5 2 1 in lights backwards
  }
  if (modeVal == 3) {
    wavesOfRainbow(5, 10); /////////////////////////////////////waves of rainbow!
  }
  if (modeVal == 4) {
    wavesOfRainbowWSV(2, 10, 50);
    firefliesDTHSOC(.01, 1500, 180, 0, false, false);
  }
  if (modeVal == 5) {
    firefliesDTHSOC(.01, 1500, 180, 255, true, true);
  }
  FastLED.show();
}
void pulsePurpleWhite() {
  float vPuWh = cos(millis() / 300.000) * 127 + 128;
  for (int i = 0; i < lct; i++) {
    leds[i] = CHSV(200, vPuWh, 160);
  }
}
void allOff() {
  for (int i = 0; i < lct; i++) {
    leds[i] = CRGB(0, 0, 0);
  }
}
void whiteWaves() {
  for (int i = 0; i < lct; i++) {
    leds[i] = CHSV(200, 0, cos((i * 6 + millis()) / 300.000) * 127 + 128);
  }
}
void allRainbowCycle(int t) {
  allHSV((millis() / t) % 256, 255, 255);
}
void allWhite(int val) {
  for (int i = 0; i < lct; i++) {
    leds[i] = CRGB(val, val, val);
  }
}
void allHSV(int valh, int vals, int valv) {
  for (int i = 0; i < lct; i++) {
    leds[i] = CHSV(valh, vals, valv);
  }
}
void allRGB(int valr, int valg, int valb) {
  for (int i = 0; i < lct; i++) {
    leds[i] = CRGB(valr, valg, valb);
  }
}
void twoFiveTwoOneInLights() {
  for (int i = 0; i < lct; i++) {
    unsigned long vTwFi = (i + millis() / 333) % 25;
    if (vTwFi == 1 || vTwFi == 2 || vTwFi == 4 || vTwFi == 5 || vTwFi == 6 || vTwFi == 7 || vTwFi == 8 || vTwFi == 10 || vTwFi == 11 || vTwFi == 13) {
      leds[i] = CRGB(255, 255, 250);
    } else {
      leds[i] = CHSV(200, 255, 80);
    }
  }
}
void twoFiveTwoOneInLightsB() {
  for (int i = 0; i < lct; i++) {
    unsigned long vTwFi = (i - millis() / 333) % 25;
    if (vTwFi == 1 || vTwFi == 3 || vTwFi == 4 || vTwFi == 6 || vTwFi == 7 || vTwFi == 8 || vTwFi == 9 || vTwFi == 10 || vTwFi == 12 || vTwFi == 13) {
      leds[i] = CRGB(255, 255, 250);
    } else {
      leds[i] = CHSV(200, 255, 80);
    }
  }
}
void allFlashPurpleWhite(int t) {
  for (int i = 0; i < lct; i++) {
    if (millis() % t * 2 < t) {
      leds[i] = CRGB(255, 0, 255);
    }
    else {
      leds[i] = CRGB(170, 170, 170);
    }
  }
}
void wavesOfRainbow(int wvs, int spd) {
  for (int i = 0; i < lct; i++) {
    leds[i] = CHSV((i * wvs * 256 / lct + millis() / spd) % 256, 255, 255);
  }
}
void allFlashRedBluePurple() {
  for (int i = 0; i < lct; i++) {
    if (millis() % 1000 < 250) {
      leds[i] = CRGB(255, 0, 255);
    }
    else if (millis() % 1000 < 500) {
      leds[i] = CRGB(255, 0, 0);
    }
    else if (millis() % 1000 < 750) {
      leds[i] = CRGB(255, 0, 255);
    }
    else {
      leds[i] = CRGB(0, 0, 255);
    }
    if (random(0, lct) < lct / 60) {
      leds[i] = CRGB(255, 255, 255);
    }
  }
}
void pulsePurple() {
  float vPulPur = cos(millis() / 700.00) * 98 + 100;
  for (int i = 0; i < lct; i++) {
    leds[i] = CRGB(vPulPur, 0, vPulPur);
  }
}
void buttonStuff() {
  if (digitalRead(buttonPin) == LOW) {
    if (b == true) {
      b = false;
      modeVal++;
      if (modeVal > maxMode) {
        modeVal = 0;
      }
    }
  }
  if (digitalRead(buttonPin) == HIGH) {
    b = true;
  }
}
void wavesOfRainbowWSV(int wvs, int spd, int v) {
  for (int i = 0; i < lct; i++) {
    leds[i] = CHSV((i * wvs * 256 / lct + millis() / spd) % 256, 255, v);
  }
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
