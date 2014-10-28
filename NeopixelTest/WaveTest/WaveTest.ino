
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

#define NUM_THETA 4

#define DELTA_PHASE 4096

uint16_t theta[NUM_THETA];

void setup()
{
  FastLED.addLeds<NEOPIXEL, DATA_PIN, RGB>(leds, NUM_LEDS);
  leds[0].setRGB(0,0,0);
  leds[1].setRGB(0,0,0);
  FastLED.show();
  memset(&theta, 0, sizeof(uint16_t) * NUM_THETA);

}

void loop()
{
//  leds[0].setHSV(0,255,sin8(theta[0]));
//  leds[1].setHSV(0,255,sin8(theta[1]));

  //leds[0].setHSV(0, 255, wavefunc(theta[0], theta[1], theta[2], theta[4]));
  int v = wavefunc(theta[0] + DELTA_PHASE, theta[1] + DELTA_PHASE, theta[2] + DELTA_PHASE, theta[3] + DELTA_PHASE);
  int w = wavefunc(theta[0], theta[1], theta[2], theta[3]);
  
  leds[1].setHSV(0, 255, v + 96);
  leds[0].setHSV(0, 255, w + 96);
  
  FastLED.show();
  
  theta[0]+= 9 + random8(3);
  theta[1]+= 11 + random8(5);
  theta[2]+= 31 + random8(7);
  theta[3]+= 33 + random8(9);
}



uint8_t sin8(uint16_t theta)
{
  uint16_t f = sin16(theta) + 32768;
  return scale16(f, 256);
}

uint8_t wavefunc(uint16_t t1, uint16_t t2, uint16_t t3, uint16_t t4)
{
  uint16_t f1 = sin16(t1) + 32768;
  uint16_t f2 = sin16(t2) + 32768;
  uint16_t f3 = sin16(t3) + 32768;
  uint16_t f4 = sin16(t4) + 32768;

  uint32_t f32 = (uint32_t)scale16(f1, 17) * (uint32_t)scale16(f2, 17) * (uint32_t)scale16(f3, 17) * (uint32_t)scale16(f4, 17);
  uint16_t f16 = (uint16_t)(min(f32, 65535));

  return scale16(f16, 160);
}










