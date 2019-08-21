#include <FastLED.h>
#define lct 288
#define pulseValPin 2//servo pulses from 600-2400 microseconds .05=blue .15=red .2-1=rainbow
#define leftDataPin 9
#define leftClockPin 8
#define rightDataPin 10
#define rightClockPin 11
#define PURPLE_HUE 200
#define RED_HUE 0
#define BLUE_HUE 160
boolean matchStarted = false;
unsigned long startMillis = 0;
int pi = 0;
CRGB ledsL[lct];
CRGB ledsR[lct];
unsigned long firefliesArray[lct];//used for fireflies() function
float ps = 0;//used for prematch
boolean pu = false;//used for prematch
float p = lct + 6;//used for prematch
int vs = 0; //used for climb
volatile unsigned long pulseStart = 0;
volatile unsigned long pulseLength = 0;
float tfi = 0.000; //used for 2521 lights
void setup() {
  FastLED.addLeds<DOTSTAR, leftDataPin, leftClockPin, BGR>(ledsL, lct);
  FastLED.addLeds<DOTSTAR, rightDataPin, rightClockPin, BGR>(ledsR, lct);
  allOff();
  FastLED.show();
  pinMode(pulseValPin, INPUT_PULLUP);
  attachInterrupt(digitalPinToInterrupt(pulseValPin), measurePulse, CHANGE);
  startP();
  startMillis = millis();
}
void loop() {
  if (micros() - pulseStart >= 65000) { //disabled
    if (matchStarted) {
      postMatch();
    }
    else {
      preMatch();
      startMillis = millis();
    }
  } else {//got signal
    matchStarted = true;
    if (pulseLength > map(18, 0, 100, 600, 2400) && pulseLength < map(102, 0, 100, 600, 2400)) {
      setAllHSV(constrain(map(pulseLength, map(20, 0, 100, 600, 2400), map(100, 0, 100, 600, 2400), 0, 255), 0, 255), 255, 255);
      FastLED.show();
    } else {
      if (pulseLength > map(0, 0, 100, 600, 2400) && pulseLength < map(9, 0, 100, 600, 2400)) {
        blue();
      }
      if (pulseLength > map(9, 0, 100, 600, 2400) && pulseLength < map(18, 0, 100, 600, 2400)) {
        red();
      }
    }
  }
}
////////////////////////////////////////////////match functions
void red() {
  if (millis() - startMillis < 15000) {
    setAllHSV(RED_HUE, 255, 155);
    FastLED.show();
  }
  else if (millis() - startMillis >= 15000 && millis() - startMillis < 130000) {
    cHSVcHSVwavesWS(CHSV(RED_HUE, 255, 115), CHSV(PURPLE_HUE, 255, 100), 3, 6);
    FastLED.show();
  }
  else if (millis() - startMillis >= 130000 && millis() - startMillis < 150000) {
    cHSVcHSVwavesWS(CHSV(RED_HUE, 255, 115), CHSV(PURPLE_HUE, 255, 100), -5, 2);
    FastLED.show();
  }
  else {
    postMatch();
  }
}
void blue() {
  if (millis() - startMillis < 15000) {
    setAllHSV(BLUE_HUE, 255, 145);
    FastLED.show();
  }
  else if (millis() - startMillis >= 15000 && millis() - startMillis < 130000) {
    cHSVcHSVwavesWS(CHSV(BLUE_HUE, 255, 105), CHSV(PURPLE_HUE, 255, 100), 3, 6);
    FastLED.show();
  }
  else if (millis() - startMillis >= 130000 && millis() - startMillis < 150000) {
    cHSVcHSVwavesWS(CHSV(BLUE_HUE, 255, 105), CHSV(PURPLE_HUE, 255, 100), -5, 2);
    FastLED.show();
  }
  else {
    postMatch();
  }
}
void preMatch() {
  wavesOfRainbowWSV(1000, 85, 90);
  if (pu == true) {
    p += 1.15;
    if (p > lct - 2) {
      pu = false;
    }
  } else {
    p -= 1.15;
    if (p <= 0) {
      pu = true;
    }
  }
  setLightHSV(p, PURPLE_HUE, 255, 255);
  setLightHSV(p + 1, PURPLE_HUE, 255, 210);
  setLightHSV(p - 1, PURPLE_HUE, 255, 210);
  setLightHSV(p + 2, PURPLE_HUE, 255, 180);
  setLightHSV(p - 2, PURPLE_HUE, 255, 180);
  setLightHSV(p + 3, PURPLE_HUE, 255, 150);
  setLightHSV(p - 3, PURPLE_HUE, 255, 150);
  setLightHSV(p + 4, PURPLE_HUE, 255, 130);
  setLightHSV(p - 4, PURPLE_HUE, 255, 130);
  setLightHSV(p + 5, PURPLE_HUE, 255, 100);
  setLightHSV(p - 5, PURPLE_HUE, 255, 100);
  FastLED.show();
}
void postMatch() {
  if (millis() - startMillis > 160000) {
    twoFiveTwoOneInLights();
  } else if (millis() - startMillis > 148000) {
    firefliesDTHSOC(50, 1000, 0, 255, true, true);
  } else {  //disabled early
    //  twoFiveTwoOneInLights();
    setAllHSV(PURPLE_HUE, 255, 20);
  }
  FastLED.show();
}
void startP() {
  for (int i = 0; i < lct + 2; i += 2) {
    setLightHSV(i - 1, 210, 255, 100);
    setLightHSV(i - 2, 210, 255, 100);
    for (int j = lct - 1; j > i - 7; j--) {
      setLightHSV(j, 0, 0, 255);
      setLightHSV(j + 1, 0, 0, 200);
      setLightHSV(j + 2, 0, 0, 150);
      setLightHSV(j + 3, 0, 0, 100);
      setLightHSV(j + 4, 0, 0, 50);
      setLightHSV(j + 5, 0, 0, 25);
      setLightHSV(j + 6, 0, 0, 10);
      setLightHSV(j + 7, 0, 0, 0);
      setLightHSV(i - 1, PURPLE_HUE, 255, 100);
      setLightHSV(i - 2, PURPLE_HUE, 255, 100);
      setLightHSV(i - 3, PURPLE_HUE, 255, 100);
      setLightHSV(i - 4, PURPLE_HUE, 255, 100);
      setLightHSV(i - 5, PURPLE_HUE, 255, 100);
      setLightHSV(i - 6, PURPLE_HUE, 255, 100);
      setLightHSV(i - 7, PURPLE_HUE, 255, 100);
      setLightHSV(i - 8, PURPLE_HUE, 255, 100);
      FastLED.show();
    }
    delay(20);
  }
}
////////////////////////////////////////////////pattern functions
void cHSVcHSVwavesWS(CHSV A, CHSV B, int W, int S) {
  CRGB a;
  CRGB b;
  hsv2rgb_rainbow(A, a);
  hsv2rgb_rainbow(B, b);
  unsigned long milli = millis();
  for (int i = 0; i < lct; i++) {
    byte scaler = sin8(int(milli / S + (i * W * 255 / lct)));
    setLightRGB(i, map(scaler, 0, 255, 0, a.red) + map(255 - scaler, 0, 255, 0, b.red), map(scaler, 0, 255, 0, a.green) + map(255 - scaler, 0, 255, 0, b.green), map(scaler, 0, 255, 0, a.blue) + map(255 - scaler, 0, 255, 0, b.blue));
  }
}
void twoFiveTwoOneInLights() {
  tfi += .08;
  if (tfi >= 25) {
    tfi = 0;
  }
  for (int i = 0; i < lct; i++) {
    if ((int(tfi) + i) % 25 == 24 || (int(tfi) + i) % 25 == 22 || (int(tfi) + i) % 25 == 21 || (int(tfi) + i) % 25 == 19 || (int(tfi) + i) % 25 == 18 || (int(tfi) + i) % 25 == 17 || (int(tfi) + i) % 25 == 16 || (int(tfi) + i) % 25 == 15 || (int(tfi) + i) % 25 == 13 || (int(tfi) + i) % 25 == 12) {
      setLightRGB(lct - i - 1, 203, 205, 190);
    } else {
      setLightHSV(lct - i - 1, PURPLE_HUE, 255, 80);
    }
  }
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
      setLightHSV(i, h, s, map(millis() - firefliesArray[i], 0, t / 2, 0, 255));
    }
    if (-firefliesArray[i] + millis() > t / 2 && -firefliesArray[i] + millis() <= t) {
      setLightHSV(i, h, s, map(millis() - firefliesArray[i], t / 2, t, 255, 0));
    }
    if (-firefliesArray[i] + millis() > t && o == true) {
      setLightRGB(i, 0, 0, 0);
    }
  }
}
void pulseHSvVT(int H, int S, int v, int V, int T) {
  unsigned long milli = millis();
  if (milli % T < T / 2) {
    setAllHSV(H, S, constrain(map(milli % T, 0, T / 2, v, V), v, V));
  }
  if (milli % T >= T / 2) {
    setAllHSV(H, S, constrain(map(milli % T, T / 2, T, V, v), v, V));
  }
}
void wavesOfRainbowWSV(int wvs, int spd, int v) {
  for (int i = 0; i < lct; i++) {
    setLightHSV(i, byte(int(i * wvs / lct + millis() * 10 / spd)), 255, v);
  }
}



/////////////////////////////////////////light setting functions (lower level)
void allOff() {
  setAllRGB(0, 0, 0);
}
void setAllHSV(int HUE, int SAT, int VAL, int S) {
  for (int i = 0; i < lct; i++) {
    setLightHSV(i, HUE, SAT, VAL, S);
  }
}
void setAllHSV(int HUE, int SAT, int VAL) {
  for (int i = 0; i < lct; i++) {
    setLightHSV(i, HUE, SAT, VAL);
  }
}
void setLightHSV(int J, int HUE, int SAT, int VAL, int S) {
  if (J >= 0 && J < lct) {
    if (S == 1) {
      ledsR[J] = CHSV(HUE, SAT, VAL);
    }
    if (S == 0) {
      ledsR[J] = CHSV(HUE, SAT, VAL);
      ledsL[J] = CHSV(HUE, SAT, VAL);
    }
    if (S == -1) {
      ledsL[J] = CHSV(HUE, SAT, VAL);
    }
  }
}
void setLightHSV(int J, int HUE, int SAT, int VAL) {
  if (J >= 0 && J < lct) {
    ledsR[J] = CHSV(HUE, SAT, VAL);
    ledsL[J] = CHSV(HUE, SAT, VAL);
  }
}
void setAllRGB(int RED, int GREEN, int BLUE, int S) {
  for (int i = 0; i < lct; i++) {
    setLightRGB(i, RED, GREEN, BLUE, S);
  }
}
void setAllRGB(int RED, int GREEN, int BLUE) {
  for (int i = 0; i < lct; i++) {
    setLightRGB(i, RED, GREEN, BLUE);
  }
}
void setLightRGB(int J, int RED, int GREEN, int BLUE, int S) {
  if (J >= 0 && J < lct) {
    if (S == 1) {
      ledsR[J] = CRGB(RED, GREEN, BLUE);
    }
    if (S == 0) {
      ledsR[J] = CRGB(RED, GREEN, BLUE);
      ledsL[J] = CRGB(RED, GREEN, BLUE);
    }
    if (S == -1) {
      ledsL[J] = CRGB(RED, GREEN, BLUE);
    }
  }
}
void setLightRGB(int J, int RED, int GREEN, int BLUE) {
  if (J >= 0 && J < lct) {
    ledsR[J] = CRGB(RED, GREEN, BLUE);
    ledsL[J] = CRGB(RED, GREEN, BLUE);
  }
}

void measurePulse() {
  if (digitalRead(pulseValPin) == HIGH) {
    pulseStart = micros();
  } else {
    if (micros() > pulseStart) {
      pulseLength = micros() - pulseStart;
    } else {
      pulseLength = 0;
      pulseStart = 0;
    }
  }
}
