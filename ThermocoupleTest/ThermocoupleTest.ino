#include <Adafruit_MAX31855.h>

#define PIN_SCLK 3
#define PIN_MISO 4
#define PIN_CS_PROBE1 5

Adafruit_MAX31855 probe1(PIN_SCLK, PIN_CS_PROBE1, PIN_MISO);

void setup()
{
	Serial.begin(9600);
}

void loop()
{
	double f = probe1.readFarenheit();
	Serial.println(f);
	delay(1000);
}
