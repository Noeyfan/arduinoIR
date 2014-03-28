int downloadPIN = 9;
//int uploadPIN = 4;
char a[]={};
char character;
boolean ft = true;
int downsig=0;
char str[4] = {'\0'};
int k =0;

//create hash to map menu name and IRcode

void setup() {
	Serial.begin(9600);// opens serial port, sets data rate to 9600 bps
}

void loop() {
  
	readstring() ;
	if (digitalRead(downloadPIN)) {
        Serial.print("0");
        k = 0;
 } 
}

void readstring() {
	while(Serial.available() > 0) {
		character = Serial.read();
                Serial.print(character);
                a[k++] = character;
		//content.concat(character);
	} 
	
}


