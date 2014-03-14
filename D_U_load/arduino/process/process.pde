import processing.serial.*;

Serial myPort;  // Create object from Serial class
String recname = "test";
int indata;

void setup() 
{
	  size(200,200); //make our canvas 200 x 200 pixels big
		  String portName = Serial.list()[0]; //change the 0 to a 1 or 2 etc. to match your port
			  myPort = new Serial(this, portName, 9600);
      myPort.bufferUntil('\n');
}
void draw() {
//	  readin();
//read2(myPort);
    /*if (read2(myPort)==57) {
      
      //delay(200);
	  sendtext(recname);
    }*/
    sendtext(recname);
}

void mousePressed() {
//	   readin();
}

void sendtext(String name) {
	  if (name == "test") {
      String textFileLines[]=loadStrings("in.data");
				  String lineItems[]=splitTokens(textFileLines[0], ",");
					  int numItems=lineItems.length;
						  for(int i = 0; i<numItems; i++){
								  myPort.write(lineItems[i]);
									  print(lineItems[i]); 
										  }
							  }
}
void readin() {
	 while (myPort.available() > 0) {
		    indata = myPort.read();
				   print(indata);
				 } 
//return indata;
}

int read2(Serial port) {
 int inString = myPort.read();
 println(inString);
 return inString;
}
