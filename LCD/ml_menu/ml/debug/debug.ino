/*
	 SD card read/write

	 This example shows how to read and write data to and from an SD card file 	
	 The circuit:
 * SD card attached to SPI bus as follows:
 ** MOSI - pin 11
 ** MISO - pin 12
 ** CLK - pin 13
 ** CS - pin 4

 created   Nov 2010
 by David A. Mellis
 modified 9 Apr 2012
 by Tom Igoe

 This example code is in the public domain.

 */

#include <SoftwareSerial.h>
#include <IRremote.h>
#include <SD.h>


// PIN 11 are used by SD card
IRrecv irrecv(A4);
decode_results results;
File myfile;

void setup()
{
	// Open serial communications and wait for port to open:
	Serial.begin(9600);
	irrecv.enableIRIn();

        if (!SD.begin(4)) {
    Serial.println("initialization failed!");
    return;
  }
  myfile = SD.open("test.txt");
  if (myfile){
    Serial.println("reading conf.txt");
    myfile.close();
  }else {
   Serial.println("error"); 
  }
}

void loop()
{
	// nothing happens after setup
	if (irrecv.decode(&results)) {
		dump(&results);
		delay(500);
		irrecv.resume(); // Receive the next value
	}
}

void dump(decode_results *results) {
	int count = results->rawlen;
	if (results->decode_type == UNKNOWN) {
		Serial.print("Unknown encoding: ");
	} 
	else if (results->decode_type == NEC) {
		Serial.print("Decoded NEC: ");
	} 
	else if (results->decode_type == SONY) {
		Serial.print("Decoded SONY: ");
	} 
	else if (results->decode_type == RC5) {
		Serial.print("Decoded RC5: ");
	} 
	else if (results->decode_type == RC6) {
		Serial.print("Decoded RC6: ");
	}
	else if (results->decode_type == PANASONIC) {	
		Serial.print("Decoded PANASONIC - Address: ");
		Serial.print(results->panasonicAddress,HEX);
		Serial.print(" Value: ");
	}
	else if (results->decode_type == JVC) {
		Serial.print("Decoded JVC: ");
	}
	Serial.print(results->value, HEX);
	Serial.print(" (");
	Serial.print(results->bits, DEC);
	Serial.println(" bits)");
	Serial.print("Raw (");
	Serial.print(count, DEC);
	Serial.print("): ");

	for (int i = 0; i < count; i++) {
		if ((i % 2) == 1) {
			Serial.print(results->rawbuf[i]*USECPERTICK, DEC);
		} 
		else {
			Serial.print(-(int)results->rawbuf[i]*USECPERTICK, DEC);
		}
		Serial.print(" ");
	}
}
