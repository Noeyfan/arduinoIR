int incomingByte;	// for incoming serial data
char a[100];
void setup() {
	Serial.begin(9600);	// opens serial port, sets data rate to 9600 bps
}

void loop() {
  //sendString();
  sendSeparate();
}

void sendString() {
 if (Serial.available() > 0) {
                incomingByte= Serial.readBytes(a,100);
		// say what you got:
		Serial.print("I received: ");
		Serial.println(incomingByte, DEC);
                for (int i=0; i<incomingByte;i++) {
                  Serial.println(a[i], DEC);
                }
	} 
}

void sendSeparate() {
 if (Serial.available() > 0) {
                incomingByte= Serial.read();
                  Serial.println(incomingByte, DEC);
	}
}

