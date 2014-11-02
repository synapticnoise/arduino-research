
#include <FastLED.h>

#define NUM_LEDS 2
#define DATA_PIN 6

#define NUM_THETA 8
#define DELTA_PHASE 32768

CRGB leds[NUM_LEDS];
uint16_t t[NUM_THETA];

void setup()
{
  FastLED.addLeds<NEOPIXEL, DATA_PIN, RGB>(leds, NUM_LEDS);
  
  // Off by default
  leds[0].setRGB(0,0,0);
  leds[1].setRGB(0,0,0);
  FastLED.show();
  
//  int seed = 0;
//
//  // Seed the RNG
//  for(int i = 0; i < 10; ++i)
//  {
//    seed += analogRead(0) * analogRead(1);
//  }
//  
//  randomSeed(seed);

  // Randomize theta values
  for(int i = 0; i < NUM_THETA; ++i)
  {
    t[i] = analogRead(0) * analogRead(1);
  }
  
}

void loop()
{
  uint16_t vRaw = wavefunc4(t[0], t[1], t[2], t[3]);
  uint16_t hRaw = wavefunc4(t[4], t[5], t[6], t[7]);

  uint16_t v = scale16(vRaw, 96);
  uint16_t h = scale16(hRaw, 32);
  
  leds[1].setHSV(18, 255 - h, 255 - v);
  leds[0].setHSV(18, 255 - h, 255 - v);

//  uint16_t v = scale16(wavefunc2(t[2], t[3]), 255);
//
//  leds[0].setHSV(64, 255, v);


  FastLED.show();
  
  // Advance theta for brightness waves
  t[0]+= 7 + random8(5);
  t[1]+= 11 + random8(5);
  t[2]+= 15 + random8(7);
  t[3]+= 55 + random8(7);
  
  // Advance theta for hue waves
  t[4]+= 6 + random8(5);
  t[5]+= 8 + random8(5);
  t[6]+= 12 + random8(5);
  t[7]+= 18 + random8(5);
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









