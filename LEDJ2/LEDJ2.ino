//led code for arduino-last updated 4/7/2017
#include <Adafruit_NeoPixel.h>
#define redAlliancePin  4 //pull low to activate   pull high if disabled
#define blueAlliancePin 3 //pull low to activate   pull high if disabled
#define shootingPin 5// pull low to activate
#define PIN 2 //led pin
#define lct 40//number of leds per strip
#define USE_SOUND true //turn off sound
#if USE_SOUND
#define soundThreshold .95
#define soundArraySize 65
#define soundPin A5//mic pin
int soundVal = 0;
int lastSoundVal = 0;
int soundArray[soundArraySize];
int soundCounter = 0;
int maxSound = 0;
int minSound = 1023;
#endif
float s = 0;
boolean lastEnabled = true;
unsigned long startMillis = 0;

boolean redAlliance  = false;
boolean blueAlliance = false;
boolean shooting = false;

boolean postMatch = false;
boolean matchStarted = false;
Adafruit_NeoPixel leds = Adafruit_NeoPixel(lct, PIN, NEO_GRB + NEO_KHZ800);

void setup() {
  leds.begin();
  for (int i = 0; i < lct; i++) {
    leds.setPixelColor(i, 0xFFFFF0);
  }
  leds.show();
  pinMode(redAlliancePin, INPUT_PULLUP);
  pinMode(blueAlliancePin, INPUT_PULLUP);
  pinMode(shootingPin, INPUT_PULLUP);
#if USE_SOUND==true
  pinMode(soundPin, INPUT_PULLUP);
#endif
  delay(500);
  start();
  startMillis = millis();
}
void loop() {
  if (digitalRead(redAlliancePin) == HIGH) {
    redAlliance = false;
  }
  else {
    redAlliance = true;
  }
  if (digitalRead(blueAlliancePin) == HIGH) {
    blueAlliance = false;
  }
  else {
    blueAlliance = true;
  }
  if (digitalRead(shootingPin) == HIGH) {
    shooting = false;
  }
  else {
    shooting = true;
  }
  if (postMatch) {
    if (lastEnabled) {
      lastEnabled = false;
      endMatch();
    }
    afterMatch();
    if (shooting) {
      lastEnabled = true;
      postMatch = false;
      matchStarted = false;
    }
  } else {
    if (blueAlliance) {
      showBlueAlliance(shooting);
    }
    if (redAlliance) {
      showRedAlliance(shooting);
    }
    if (!redAlliance && !blueAlliance) {
      if (matchStarted) {
        gotDisabled();
      } else {
        disabled();
        startMillis = millis();
      }
    }
  }
}
void disabled() {
  s = int(s + 20) % 6000;
  for (float i = 0; i <= lct; i++) {
    leds.setPixelColor(i, gRain(int((9000 * i / lct) + s) % 6000) , 0, gRain(int((9000 * i / lct) + s) % 6000));
  }
  sound();
#if USE_SOUND==false
  leds.show();
#endif
}
void gotDisabled() {
  if (millis() - startMillis >= 150000) {
    postMatch = true;
  }
  s = int(s + 1) % 400;
  if (s >= 200) {
    for (float i = 0; i <= lct; i++) {
      leds.setPixelColor(i, 190 / 3, 0, 255 / 3);
    }
  }
  else {
    for (float i = 0; i <= lct; i++) {
      leds.setPixelColor(i, 0, 0, 0);
    }
  }
  leds.setPixelColor(map(millis() - startMillis, 15000, 150000, 0, lct), 0xFFFFFF);
  sound();
#if USE_SOUND==false
  leds.show();
#endif
}
void sound() {
#if USE_SOUND==true
  lastSoundVal = soundVal;
  soundVal = analogRead(soundPin);
  soundArray[soundCounter] = abs(soundVal - lastSoundVal);
  soundCounter++;
  soundCounter = soundCounter % soundArraySize;
  maxSound = 0;
  minSound = 1023;
  for (int i = 0; i < soundArraySize; i++) {
    if (soundArray[i] > maxSound) {
      maxSound = soundArray[i];
    }
    if (soundArray[i] < minSound) {
      minSound = soundArray[i];
    }
  }
  if (abs(soundVal - lastSoundVal) >= (soundThreshold * (maxSound - minSound)) && maxSound - minSound > 5) {
    for (int i = 0; i <= lct; i++) {
      leds.setPixelColor(i, 0xFFFFFF);
    }
    leds.show();
    delay(10);
  }
  else {
    leds.show();
  }
#endif
}
void endMatch() {
  for (int x = 0; x < 30; x++) {
    for (int i = 0; i <= lct; i++) {
      int t = random(0, 6000);
      leds.setPixelColor(i, aRain(t), gRain(t), bRain(t));
    }
    leds.show();
    delay(250);
  }
}
void afterMatch() {
  s = int(s + 1) % 6000;
  for (float i = 0; i <= lct; i++) {
    leds.setPixelColor(i, aRain(int(3 * s) % 6000) / 5, gRain(int(3 * s) % 6000) / 5, bRain(int(3 * s) % 6000) / 5);
  }
  leds.setPixelColor(map(s, 0, 6000, lct, -17) + 1, 0xD000FF);
  leds.setPixelColor(map(s, 0, 6000, lct, -17) + 2, 0xD000FF);

  leds.setPixelColor(map(s, 0, 6000, lct, -17) + 5, 0xD000FF);
  leds.setPixelColor(map(s, 0, 6000, lct, -17) + 6, 0xD000FF);
  leds.setPixelColor(map(s, 0, 6000, lct, -17) + 7, 0xD000FF);
  leds.setPixelColor(map(s, 0, 6000, lct, -17) + 8, 0xD000FF);
  leds.setPixelColor(map(s, 0, 6000, lct, -17) + 9, 0xD000FF);

  leds.setPixelColor(map(s, 0, 6000, lct, -17) + 12, 0xD000FF);
  leds.setPixelColor(map(s, 0, 6000, lct, -17) + 13, 0xD000FF);

  leds.setPixelColor(map(s, 0, 6000, lct, -17) + 16, 0xD000FF);
  leds.show();
}
void showBlueAlliance(boolean s) {
  matchStarted = true;
  if (s) {
    blueShoot();
  }
  else if (millis() - startMillis < 15000) {
    blueAuto();
  }
  else if (millis() - startMillis >= 15000 && millis() - startMillis < 120000) {
    blueTele();
  }
  else if (millis() - startMillis >= 120000 && millis() - startMillis < 150000) {
    blueClimb();
  }
  if (millis() - startMillis >= 150000) {
    postMatch = true;
  }
}
void showRedAlliance(boolean s) {
  matchStarted = true;
  if (s) {
    redShoot();
  }
  else if (millis() - startMillis < 15000) {
    redAuto();
  }
  else if (millis() - startMillis >= 15000 && millis() - startMillis < 120000) {
    redTele();
  }
  else if (millis() - startMillis >= 120000 && millis() - startMillis < 150000) {
    redClimb();
  }
  if (millis() - startMillis >= 150000) {
    postMatch = true;
  }
}
void blueShoot() {
  for (int i = 0; i <= lct; i++) {
    leds.setPixelColor(i, 0, 10, 35);
  }
  s = int(s + 1) % ((lct * 2));
  if (s < lct) {
    leds.setPixelColor(s + 1, 140, 0, 255);
    leds.setPixelColor(s, 110, 0, 190);
    leds.setPixelColor(s - 1, 90, 0, 170);
    leds.setPixelColor(s - 2, 70, 0, 150);
    leds.setPixelColor(s - 3, 50, 0, 120);
    leds.setPixelColor(s - 4, 40, 0, 100);
    leds.setPixelColor(s - 5, 20, 0, 85);
    leds.setPixelColor(s - 6, 10, 0, 70);
  }
  if (s >= lct) {
    leds.setPixelColor(-(s) + 2 * lct + 6, 10, 0, 70);
    leds.setPixelColor(-(s) + 2 * lct + 5, 20, 0, 85);
    leds.setPixelColor(-(s) + 2 * lct + 4, 40, 0, 100);
    leds.setPixelColor(-(s) + 2 * lct + 3, 50, 0, 120);
    leds.setPixelColor(-(s) + 2 * lct + 2, 70, 0, 150);
    leds.setPixelColor(-(s) + 2 * lct + 1, 90, 0, 170);
    leds.setPixelColor(-(s) + 2 * lct, 110, 0, 190);
    leds.setPixelColor(-(s) + 2 * lct - 1, 140, 0, 255);
  }
  leds.show();
  delay(20);
}
void redShoot() {
  for (int i = 0; i <= lct; i++) {
    leds.setPixelColor(i, 25, 0, 0);
  }
  s = int((s + 1)) % ((lct * 2));
  if (s < lct) {
    leds.setPixelColor(s + 1, 205, 0, 255);
    leds.setPixelColor(s, 160, 0, 180);
    leds.setPixelColor(s - 1, 100, 0, 110);
    leds.setPixelColor(s - 2, 90, 0, 100);
    leds.setPixelColor(s - 3, 60, 0, 70);
    leds.setPixelColor(s - 4, 40, 0, 50);
    leds.setPixelColor(s - 5, 30, 0, 30);
    leds.setPixelColor(s - 6, 20, 0, 10);
  }
  if (s >= lct) {
    leds.setPixelColor(-(s) + 2 * lct + 6, 20, 0, 10);
    leds.setPixelColor(-(s) + 2 * lct + 5, 30, 0, 30);
    leds.setPixelColor(-(s) + 2 * lct + 4, 40, 0, 50);
    leds.setPixelColor(-(s) + 2 * lct + 3, 60, 0, 70);
    leds.setPixelColor(-(s) + 2 * lct + 2, 90, 0, 100);
    leds.setPixelColor(-(s) + 2 * lct + 1, 100, 0, 110);
    leds.setPixelColor(-(s) + 2 * lct, 160, 0, 180);
    leds.setPixelColor(-(s) + 2 * lct - 1, 205, 0, 255);
  }
  leds.show();
  delay(20);
}
void blueAuto() {
  s = int((s + 50)) % 6000;
  for (float i = 0; i <= lct; i++) {
    leds.setPixelColor(i, aRain(int(s + (i / lct * 11000)) % 6000) / 2, gRain(int(s + (i / lct * 11000)) % 6000) / 2, bRain(int(s + (i / lct * 11000)) % 6000) / 2);
  }
  leds.show();
}
void redAuto() {
  s = int((s + 50)) % 6000;
  for (float i = 0; i <= lct; i++) {
    leds.setPixelColor(i, aRain(int(s + (i / lct * 11000)) % 6000) / 2, gRain(int(s + (i / lct * 11000)) % 6000) / 2, bRain(int(s + (i / lct * 11000)) % 6000) / 2);
  }
  leds.show();
}
void blueTele() {
  s = int((s + 4)) % 6000;
  for (int i = 0; i < lct; i++) {
    leds.setPixelColor(i, (210 / 2)*sin(TWO_PI * (s) / 6000) + (210 / 2), 0, 255);
  }
  leds.setPixelColor(map(millis() - startMillis, 15000, 150000, 0, lct), 0xFFFFFF);
  leds.show();
}

void redTele() {
  s = int((s + 4)) % 6000;
  for (int i = 0; i < lct; i++) {
    leds.setPixelColor(i, 255 , 0, (200 / 2)*sin(TWO_PI * (s) / 6000) + (200 / 2));
  }
  leds.setPixelColor(map(millis() - startMillis, 15000, 150000, 0, lct), 0xFFFFFF);
  leds.show();
}

void blueClimb() {
  for (int i = 0; i < lct; i++) {
    leds.setPixelColor(i, 0x0000DF);
  }
  s += amap(millis() - startMillis - 120000, 0, 30000, 1, 5);
  if (s >= lct * 10) {
    s = -70;
  }
  leds.setPixelColor(map(millis() - startMillis, 15000, 150000, 0, lct), 0xFFFFFF);
  leds.setPixelColor(s / 10 + 1, 0xEF00FF);
  leds.setPixelColor(s / 10 + 2, 0xEF00FF);
  leds.setPixelColor(s / 10 + 3, 0xEF00FF);
  leds.setPixelColor(s / 10 + 4, 0xEF00FF);
  leds.setPixelColor(s / 10 + 5, 0xEF00FF);
  leds.setPixelColor(s / 10 + 6, 0xEF0FF);
  leds.show();
  delay(1);
}
void redClimb() {
  for (int i = 0; i < lct; i++) {
    leds.setPixelColor(i, 0xFF0000);
  }
  s += amap(millis() - startMillis - 120000, 0, 30000, 1, 5);
  if (s >= lct * 10) {
    s = -70;
  }
  leds.setPixelColor(map(millis() - startMillis, 15000, 150000, 0, lct), 0xFFFFFF);
  leds.setPixelColor(s / 10 + 1, 0xEF00FF);
  leds.setPixelColor(s / 10 + 2, 0xE000FF);
  leds.setPixelColor(s / 10 + 3, 0xE000FF);
  leds.setPixelColor(s / 10 + 4, 0xE000FF);
  leds.setPixelColor(s / 10 + 5, 0xE000FF);
  leds.setPixelColor(s / 10 + 6, 0xE000FF);
  leds.show();
  delay(1);
}
void start() {
  resetAll();
  for (int i = 0; i <= lct; i++) {
    for (int j = lct; j > i; j--) {
      leds.setPixelColor(j + 1, 0x000000);
      leds.setPixelColor(j, 0xFFFFF0);
      leds.show();
      delay(amap(i, 0, lct, 1, 20));
    }
    leds.setPixelColor(i + 1, 0x000000);
    leds.setPixelColor(i, 0xAF00EF);
    leds.show();
    delay(10);
  }
  delay(100);
  resetAll();
}
byte aRain(int h) {
  float a = 255;
  if (h >= 0 && h < 1000) {
    a = amap(h, 0, 1000 / 6, 255, 255);
  }
  if (h >= 1000 && h < 2000) {
    a = amap(h, 1000, 2000, 255, 0);
  }
  if (h >= 2000 && h < 3000) {
    a = amap(h, 2000, 3000, 0, 0);
  }
  if (h >= 3000 && h < 4000) {
    a = amap(h, 3000, 4000, 0, 0);
  }
  if (h >= 4000 && h < 5000) {
    a = amap(h, 4000, 5000, 0, 255);
  }
  if (h >= 5000 && h <= 6000) {
    a = amap(h, 5000, 6000, 255, 255);
  }
  return a;
}

byte gRain(int h) {
  float a = 0;
  if (h >= 0 && h < 1000) {
    a = amap(h, 0, 1000, 0, 255);
  }
  if (h >= 1000 && h < 2000) {
    a = amap(h, 1000, 2000, 255, 255);
  }
  if (h >= 2000 && h < 3000) {
    a = amap(h, 2000, 3000, 255, 255);
  }
  if (h >= 3000 && h < 4000) {
    a = amap(h, 3000, 4000, 255, 0);
  }
  if (h >= 4000 && h < 5000) {
    a = amap(h, 4000, 5000, 0, 0);
  }
  if (h >= 5000 && h <= 6000) {
    a = amap(h, 5000, 6000, 0, 0);
  }
  return a;
}

byte bRain(int h) {
  float a = 0;
  if (h >= 0 && h < 1000) {
    a = amap(h, 0, 1000 / 6, 0, 0);
  }
  if (h >= 1000 && h < 2000) {
    a = amap(h, 1000, 2000, 0, 0);
  }
  if (h >= 2000 && h < 3000) {
    a = amap(h, 2000, 3000, 0, 255);
  }
  if (h >= 3000 && h < 4000) {
    a = amap(h, 3000, 4000, 255, 255);
  }
  if (h >= 4000 && h < 5000) {
    a = amap(h, 4000, 5000, 255, 255);
  }
  if (h >= 5000 && h <= 6000) {
    a = amap(h, 5000, 6000, 255, 0);
  }
  return a;
}
void resetAll() {
  for (int i = 0; i < lct; i++) {
    leds.setPixelColor(i, 0x000000);
    leds.show();
  }
}
float amap(float x, float in_min, float in_max, float out_min, float out_max)
{
  return (x - in_min) * (out_max - out_min) / (in_max - in_min) + out_min;
}

