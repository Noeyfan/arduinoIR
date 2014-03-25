#include <SoftwareSerial.h>
#include <IRremote.h>
#include <SerialLCD.h>
#include <string>

char inbyte;
String indata="";
int buttonPin = 9;
int downloadPin = 6;
int RECV_PIN = 11;
unsigned int data[300]={0};
int count =0;
SerialLCD slcd(11,12);
IRsend irsend;


const char* m[15][15] = {{"TV", "Vup", "CHup", "Back"},
                       {"DVD", "Dup", "DHup", "Vup","Vdown","Xup","Yup","Zup","Wup","Back" },
                       {"Ref", "Ropen", "Rclose", "Back"},
                       {"MicW", "Mopen", "Mclose", "Back"},
                  };


                 
void setup() {
  Serial.begin(9600);
    slcd.begin();
    pinMode(buttonPin,INPUT);
    slcd.backlight();
}

void loop() {
  readin();
  int i =0;
  int j =1;
  while(m[i-1][j-1] != '\0') {
      slcd.setCursor(0,0);
      slcd.print (m[i++][0]);
       delay(1000);
    if(digitalRead(buttonPin)) {
     Serial.print(i);
     while(m[i-1][j] != '\0') {
     slcd.clear();
     slcd.setCursor(0,0);
     //have to set display when press on the last menu

       slcd.print(m[i-1][0]); 
       slcd.setCursor(0,1);
       slcd.print(m[i-1][j++]);
       delay(1000);
       //TODO add send signal
       if (digitalRead(buttonPin) && m[i-1][j] != '\0') {
         slcd.clear();
         slcd.setCursor(0,1);
         slcd.print("sent");
         sendSignal(data,count);
         delay(500);
         j=j-1;
       }
       //TODO Manually DOWNLOAD the code
       else if (digitalRead(downloadPin)) {
         readin();
       }
     }
       j=1;
       slcd.clear();
    }
  }
    slcd.clear();
}

void sendSignal(unsigned int sig[], int num) {
  //TODO add send signal
  irsend.sendRaw(sig, num, 38);
}

void readin() {
  if (Serial.available()) {
    inbyte = Serial.read();
    indata.concat(inbyte);
  }
  if (indata != "") {
    Serial.println(indata);
  }
}
