import processing.serial.*;
Serial myPort;
String val;

boolean firstContact = false;

void setup()
{
	size(200,200);
	myPort = new Serial(this, Serial.list()[0],9600);
	myPort.bufferUntil('\n');
	myPort.write('C');
}

void draw()
{
}


void serialEvent(Serial myPort)
{
	val = myPort.readStringUntil('\n');
	if (val != null) {
		val = trim(val);
		println(val, count++);
	}
	if (count == 15) {
		myPort.write('C');
	}

	//if (!firstContact) {
	//	if (val.equals("A")) {
	//		myPort.clear();
	//		firstContact = true;
	//		myPort.write("A");
	//		println("A");
	//		println("contact");
	//	}else {
	//		println(val);
	//		if (mousePressed) {
	//			myPort.write('1');
	//			println("1");
	//		}
	//		myPort.write("A");
	//	}
	//}
}
