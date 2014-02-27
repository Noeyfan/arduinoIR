#include <SoftwareSerial.h>

#include <SerialLCD.h>

int tempPin = 0;
int buttonPin = 10;
SerialLCD slcd(11,12);
char* m[] = {"TV","Air","Fre","MicW"};
int count = 0;

void setup() {
    slcd.begin();
    pinMode(buttonPin,INPUT);
    slcd.backlight();
    slcd.setCursor(0,0);
    slcd.print(m[count]);
}

void loop() {
   while(count <= 3) {
   	if(digitalRead(buttonPin)) {
                         slcd.setCursor(0,0);
	 	 	 slcd.print(m[++count]);
   	   delay(200);
 	  	}
		}
		count =0;
                slcd.clear();
                slcd.setCursor(0,0);
	 	slcd.print(m[count]);
	}
