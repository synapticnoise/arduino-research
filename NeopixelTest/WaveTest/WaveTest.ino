
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

#define NUM_THETA 8

#define DELTA_PHASE 32768

uint16_t t[NUM_THETA];

void setup()
{
  FastLED.addLeds<NEOPIXEL, DATA_PIN, RGB>(leds, NUM_LEDS);
  leds[0].setRGB(0,0,0);
  leds[1].setRGB(0,0,0);
  FastLED.show();
  memset(&t, 0, sizeof(uint16_t) * NUM_THETA);

}

/*
TODO: Try inverting the wave function output
TODO: Map wave function onto hue

*/

void loop()
{
//  leds[0].setHSV(0,255,sin8(theta[0]));
//  leds[1].setHSV(0,255,sin8(theta[1]));

  //leds[0].setHSV(0, 255, wavefunc(theta[0], theta[1], theta[2], theta[4]));
  //uint16_t v = wavefunc(theta[0] + DELTA_PHASE, theta[1] + DELTA_PHASE, theta[2] + DELTA_PHASE, theta[3] + DELTA_PHASE);
  //uint16_t w = wavefunc(theta[0], theta[1], theta[2], theta[3]);
  
  uint16_t vRaw = wavefunc4(t[0], t[1], t[2], t[3]);
  uint16_t hRaw = wavefunc4(t[4], t[5], t[6], t[7]);

  uint16_t v = scale16(vRaw, 96);
  uint16_t h = scale16(hRaw, 6);
  
  
  leds[1].setHSV(16 - h, 255, 255 - v);
  leds[0].setHSV(16 - h, 255, 255 - v);

  FastLED.show();
  
  t[0]+= 23 + random8(5);
  t[1]+= 17 + random8(5);
  t[2]+= 98 + random8(21);
  t[3]+= 97 + random8(31);
  
  t[4]+= 19 + random8(5);
  t[5]+= 17 + random8(5);
  t[6]+= 21 + random8(5);
  t[7]+= 23 + random8(5);
}

uint8_t sin8(uint16_t theta)
{
  uint16_t f = sin16(theta) + 32768;
  return scale16(f, 256);
}

uint16_t wavefunc4(uint16_t t1, uint16_t t2, uint16_t t3, uint16_t t4)
{
  uint16_t f1 = sin16(t1) + 32768;
  uint16_t f2 = sin16(t2) + 32768;
  uint16_t f3 = sin16(t3) + 32768;
  uint16_t f4 = sin16(t4) + 32768;

  uint32_t f32 = (uint32_t)scale16(f1, 17) * (uint32_t)scale16(f2, 17) * (uint32_t)scale16(f3, 17) * (uint32_t)scale16(f4, 17);
  uint16_t f16 = (uint16_t)(min(f32, 65535));

  return f16;
}

uint16_t wavefunc2(uint16_t t1, uint16_t t2)
{
  uint16_t f1 = sin16(t1) + 32768;
  uint16_t f2 = sin16(t2) + 32768;

  uint32_t f32 = (uint32_t)scale16(f1, 257) * (uint32_t)scale16(f2, 257);
  uint16_t f16 = (uint16_t)(min(f32, 65535));

  return f16;
}









