#include <Servo.h>

#define PIN_SERVO_RIGHT 13
#define PIN_SERVO_LEFT 12
#define PIN_SERVO_SONAR 11

const int __ServoSonarMin = 38;
const int __ServoSonarMax = 152;

int __offsetLeft = 7;
int __offsetRight = 0;

Servo servoLeft;
Servo servoRight;
Servo servoSonar;



void setup()
{
	Serial.begin(115200);
	servoLeft.attach(PIN_SERVO_LEFT);
	servoRight.attach(PIN_SERVO_RIGHT);
	servoSonar.attach(PIN_SERVO_SONAR);
	setSpeed(0.0, 0.0);
}

int aimPoints[] = {-90, -45, 0, 45, 90};
int curPointIndex = 0;
int numPoints = sizeof(aimPoints) / sizeof(int);
int increment = 1;

void loop()
{
	Serial.println(aimPoints[curPointIndex]);
	aimSonar(aimPoints[curPointIndex]);
	curPointIndex += increment;
	if(curPointIndex >= numPoints)
	{
		curPointIndex = numPoints - 1;
		increment = -1;
	}
	else if(curPointIndex < 0)
	{
		curPointIndex = 0;
		increment = 1;
	}

	delay(1000);

}

void setSpeed(float left, float right)
{
	int deltaRight = 0 - round(left * 200.0);
	int deltaLeft = round(right * 200.0);
	servoRight.writeMicroseconds(1500 + deltaRight + __offsetRight);
	servoLeft.writeMicroseconds(1500 + deltaLeft + __offsetLeft);
}

void aimSonar(int relativeDegrees)
{
	int value = map(relativeDegrees, -90, 90, __ServoSonarMin, __ServoSonarMax);
	servoSonar.write(value);
}