#include <SoftwareSerial.h>
#include <SerialLCD.h>

SerialLCD slcd(5,6);

void setup()
{
	slcd.begin();
	slcd.print("hello,world");
}

void loop()
{
	slcd.noDisplay();
	delay(1000);
	slcd.display();
	delay(1000);
}
