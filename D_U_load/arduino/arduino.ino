int incomingByte;	// for incoming serial data
int downloadPIN = 9;
//int uploadPIN = 4;
char a[100];
String content="";
char character;
boolean ft=true;
int downsig=9;
//create hash to map menu name and IRcode

void setup() {
	Serial.begin(9600);// opens serial port, sets data rate to 9600 bps
}

void loop() {
	if (digitalRead(downloadPIN)) {
          //Serial.println("b pressed");
          /*if (ft){
           Serial.print(downsig);
           //Serial.flush();
           //Serial.println("write 1");
           ft=false;
          }*/
  	  readstring();
	}

     /* if (digitalRead(uploadPIN)) {
        if (ft){
           Serial.write(2);
           //Serial.println("write 1");
           ft=false;
      }
      sendint();
}*/
}

void readstring() {
 while(Serial.available() > 0) {
  character = Serial.read();
  Serial.flush();
  content.concat(character);
 } 
 if(content !="") {
  Serial.print(content); 
  content="";
 }
}

void sendint() {
        /*things to be dumped*/
	//Serial.write(1);
}
