
#include <FastLED.h>

#define NUM_LEDS 2
#define DATA_PIN 6

#define MIN_HUE 16
#define MAX_HUE 24
#define MID_HUE ((MAX_HUE-MIN_HUE)/2)+MIN_HUE

#define MIN_SAT 192
#define MAX_SAT 255
#define MID_SAT ((MAX_SAT-MIN_SAT)/2)+MIN_SAT

#define MIN_VAL 128
#define MAX_VAL 255
#define MID_VAL ((MAX_VAL-MIN_VAL)/2)+MIN_VAL

CRGB leds[NUM_LEDS];

CHSV hsv[NUM_LEDS];

void setup()
{
  FastLED.addLeds<NEOPIXEL, DATA_PIN, RGB>(leds, NUM_LEDS);
//  hsv[0].setHSV(MID_HUE, MID_SAT, MID_VAL);
//  hsv[1].setHSV(MID_HUE, MID_SAT, MID_VAL);
  leds[0].setHSV(64,255,255);
  leds[0].setHSV(64,255,255);
  FastLED.show();
  delay(5000);
  leds[0].setHSV(48,255,255);
  leds[0].setHSV(48,255,255);
  FastLED.show();
  delay(5000);
  leds[0].setHSV(32,255,255);
  leds[0].setHSV(32,255,255);
  FastLED.show();
  delay(5000);


  hsv[0].setHSV(MID_HUE, MAX_SAT, MAX_VAL);
  hsv[1].setHSV(MID_HUE, MAX_SAT, MAX_VAL);
  leds[0] = hsv[0];
  leds[1] = hsv[1];
  FastLED.show();
  delay(2000);
}

void loop()
{
  update(0);
  update(1);
  leds[0] = hsv[0];
  leds[1] = hsv[1];
  FastLED.show();
  delay(10);  
}

void update(int ledNum)
{
  int d = getDirection();  
  hsv[ledNum].h = constrain(hsv[ledNum].h + d, MIN_HUE, MAX_HUE);
  
//  d = getDirection();  
//  hsv[ledNum].s = constrain(hsv[ledNum].s + d, MIN_SAT, MAX_SAT);
 
  d = getDirection();  
  hsv[ledNum].v = constrain(hsv[ledNum].v + d, MIN_VAL, MAX_VAL);
}

int getDirection()
{
  int r = random(10);
  return r < 3 ? -1 :
  r < 7 ? 0 : 1;
}



