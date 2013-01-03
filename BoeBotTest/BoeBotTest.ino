#include <Servo.h>

#define PIN_SERVO_RIGHT 13
#define PIN_SERVO_LEFT 12

int __offsetLeft = 7;
int __offsetRight = 0;

Servo servoLeft;
Servo servoRight;

void setup()
{
	Serial.begin(115200);
	servoLeft.attach(PIN_SERVO_LEFT);
	servoRight.attach(PIN_SERVO_RIGHT);
}

void loop()
{
	setSpeed(0.0, 0.0);
	delay(1000);
	setSpeed(1.0, 1.0);
	delay(5000);
	setSpeed(0.0, 0.0);
	delay(500);
	setSpeed(1.0, -1.0);
	delay(1000);
}

void setSpeed(float left, float right)
{
	int deltaRight = 0 - round(left * 200.0);
	int deltaLeft = round(right * 200.0);

	Serial.print(deltaRight);
	Serial.print(", ");
	Serial.println(deltaLeft);

	servoRight.writeMicroseconds(1500 + deltaRight + __offsetRight);
	servoLeft.writeMicroseconds(1500 + deltaLeft + __offsetLeft);
}