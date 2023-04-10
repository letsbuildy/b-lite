#include <Adafruit_NeoPixel.h>
#include "blite.h"
#define NUMPIXELS 24

const int PIN = io2;

Adafruit_NeoPixel pixels = Adafruit_NeoPixel(NUMPIXELS, PIN, NEO_GRB + NEO_KHZ800);

void setup() {
  pixels.begin();
}

void loop() {
set_all(255,0,0);
delay(5000);
set_all(0,255,0);
delay(5000);
set_all(0,0,255);
delay(5000);
set_all(255,255,0);
delay(5000);
set_all(255,0,255);
delay(5000);
set_all(0,255,255);
delay(5000);
set_all(255,255,255);
delay(5000);
}
void set_all(int r, int g, int b) {
  for(int i=0;i<NUMPIXELS;i++){

  pixels.setPixelColor(i, pixels.Color(r,g,b));

  pixels.show();
  }
}
