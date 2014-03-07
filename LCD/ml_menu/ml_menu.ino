#include <SoftwareSerial.h>

#include <SerialLCD.h>

int tempPin = 0;
int buttonPin = 9;
SerialLCD slcd(11,12);
const char* m[6][6] = {{"TV", "Vup", "CHup", "Back"},
                       {"DVD", "Dup", "DHup", "Back" },
                       {"Ref", "Ropen", "Rclose", "Back"},
                       {"MicW", "Mopen", "Mclose", "Back"},
                  };
//m[0][0]="TV";
//m[1][0]="DVD";
//m[2][0]="Air";
//m[3][0]="Fre";
//m[4][0]="MicW";
int i =0;
int j =1;
void setup() {
    slcd.begin();
    pinMode(buttonPin,INPUT);
    slcd.backlight();
    slcd.setCursor(0,0);
    slcd.print(m[i][0]);
    delay(100);
}

void loop() {
  while(i <= 4) {
    slcd.setCursor(0,0);
    slcd.print (m[i][0]);
    if(digitalRead(buttonPin)) {
     while(j < 4) {
     slcd.clear();
     slcd.setCursor(0,0);
     slcd.print(m[i-1][0]); 
     slcd.setCursor(0,1);
     slcd.print(m[i-1][j++]);
     delay(1000);
     }
       j=1;
       slcd.clear();
    }
        i++;
        delay(1000);
  }
  i = 0;
  slcd.clear();
  slcd.setCursor(0,0);
  slcd.print(m[0][0]);
  slcd.setCursor(0,1);
}
