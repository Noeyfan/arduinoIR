#include <SoftwareSerial.h> 
#include <IRremote.h> 
#include <SerialLCD.h> 
#include <SD.h> 

SerialLCD slcd(11, 12);
File myFile;


void setup()
{
	Serial.begin(9600);
	Serial.print("Initializing SD card...");
	pinMode(10, OUTPUT);

	if (!SD.begin(4)) {
		Serial.println("initialization failed!");
		return;
	}
}

void loop()
{
	slcd.print("Hello World");
	delay(1000);
}

