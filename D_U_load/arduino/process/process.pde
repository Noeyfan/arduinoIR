// Example by Tom Igoe

import processing.serial.*;

Serial myPort;  // The serial port
boolean fg = true;
void setup() {
  // List all the available serial ports:
  println(Serial.list());
  // Open the port you are using at the rate you want:
  myPort = new Serial(this, Serial.list()[0], 9600);
}

void draw() {
download("test");
  }


 void download(String name) {
    while (myPort.available() > 0) {
    String inBuffer = myPort.readString();   
    if (inBuffer.charAt(0) == '0'  && fg ){
      println(inBuffer.charAt(0));
      sendtext(name);
        fg = false;
    }
    } 
 }
  
void sendtext(String name) {
if (name == "test") {
     String textFileLines[]=loadStrings("in.data");
     String lineItems[]=splitTokens(textFileLines[0], ",");
     int numItems=lineItems.length;
     for(int i = 0; i<numItems; i++){
       myPort.write(lineItems[i]);
       print(lineItems[i]);
       //delay(500);
    }
  }
}
