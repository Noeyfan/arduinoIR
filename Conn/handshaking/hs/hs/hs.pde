import processing.serial.*;

Serial myPort;  // The serial port
OutputStream fout;
int i = 0;

void setup() {
	size(500,200);
	background(255);
	// List all the available serial ports:
	println(Serial.list());
	// Open the port you are using at the rate you want:
	myPort = new Serial(this, Serial.list()[0],9600);

	//create file writer
	fout = createOutput("conf.txt");
	//fout = createOutput("sig.txt");

	//set guide
	PFont f;
	f = createFont("Arial",16,true);
	textFont(f,16);
	fill(0,0,255);
	text("Please plugin the IRremote and press the upload button to upload ",10,80);
	text("Settings would be saved to conf.txt ",10,110);
}

void draw() {
	while (myPort.available() > 0) {
		byte[] inBuffer = myPort.readBytes();
		if (inBuffer != null) {
			try {
			fout.write(inBuffer);
			fout.flush();
			} catch(Exception e) {
			}
			print(inBuffer);
			if (i <= 450) {
				rect(10,130,i,20);
				i += 55;
			}else {
				rect(10,130,450,20);
			}
			stroke(0,0,255);
			fill(0,0,255);
		}
	}
}

void mousePressed() {
	i = 0;
}
