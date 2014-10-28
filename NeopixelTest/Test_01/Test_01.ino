#include <FastLED.h>

#define NUM_LEDS 2
#define DATA_PIN 6
#define LED_PULSE_PIN 13

#define MIN_HUE 0
#define MAX_HUE 255

int curHue = MIN_HUE;
boolean ledState = false;  
CRGB leds[NUM_LEDS];

void setup()
{
  pinMode(LED_PULSE_PIN, OUTPUT);
  pulse();
  FastLED.addLeds<NEOPIXEL, DATA_PIN>(leds, NUM_LEDS);
}


void loop()
{
  CHSV hsv(curHue,255,255);
  hsv2rgb_rainbow(hsv, leds[0]);
  hsv2rgb_spectrum(hsv, leds[1]);  
  
  if(++curHue > MAX_HUE)
    {
    curHue = MIN_HUE;
    pulse();
    }
  
  delay(5);
}

void pulse()
{
  ledState = !ledState;
  digitalWrite(LED_PULSE_PIN, ledState ? HIGH : LOW);
}

