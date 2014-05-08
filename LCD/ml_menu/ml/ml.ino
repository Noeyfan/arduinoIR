#include <SoftwareSerial.h>
#include <IRremote.h>
#include <SerialLCD.h>
#include <SD.h>

File myFile;
char inbyte;
String indata="";
int buttonPin = 9;
int uploadPin = 13;
int learnPin = 5;
SerialLCD slcd(7,8);
IRsend irsend;
IRrecv irrecv(A4);
decode_results results;

int i = 0;
int sub_count = 0;
int sub_start = 0;

//signal is acutually a cache
struct Signal {
	unsigned int code[69];
};

char menu[5][10] = {"TV", "DVD", "AIR", ""};
char sub_menu[10][10] = {"UP", "DOWN", "VUP", "UP", "DOWN", "OPEN", "CLOSE"};
int entry[] = {0, 3, 5, 7};
Signal signal[1];

//int signal[] = {1, 1, 2, 2, 2, 3, 3, 4, 4, 5, 7};
//int signal_entry[] = {0, 2, 5, 7, 9, 10, 10, 11};

//char menu[5][10];
//char sub_menu[10][10];
//int entry[4];
//int signal[11];
//int signal_entry[8];

int buttonState = 0;         // variable for reading the pushbutton status

void read_to_array(File file, uint8_t* arr, int n) {
	int i;
	for (i = 0; i < n; i++) {
		if ((arr[i] = file.read()) == -1) {
			Serial.println("a byte is expected but failed");
			break;
		}
	}
}

void setup() {
	Serial.begin(9600);
	slcd.begin();
	irrecv.enableIRIn();
	pinMode(buttonPin,INPUT);
	slcd.backlight();
	pinMode(10, OUTPUT);
	//slcd.print("Hello, world");
	//delay(1000);
	if (!SD.begin(4)) {
		Serial.println("initialization failed!");
		return;
	}
	//open menu file
	myFile = SD.open("conf.txt");
	if (myFile) {
		//read_to_array(myFile, menu);
		//read_to_array(myFile, sub_menu);
		//read_to_array(myFile, entry);
		myFile.close();
	} else {
		// if the file didn't open, print an error:
		Serial.println("error opening conf.txt");
	}
}


int status = 0; // 0 for main menu; 1 for sub menu; 
int main_cursor = 0;
int sub_cursor = 0;

void loop()
{
	buttonState = digitalRead(uploadPin); //record the button state
	if (buttonState == HIGH) {
		slcd.clear();
		slcd.setCursor(0,0);
		slcd.print("Uploading");
		slcd.setCursor(0,1);
		slcd.print("..");
		Serial.write((uint8_t*)menu,sizeof(menu));
		delay(1000);
		slcd.setCursor(0,1);
		slcd.print("....");
		Serial.write((uint8_t*)sub_menu, sizeof(sub_menu));
		delay(1000);
		slcd.setCursor(0,1);
		slcd.print("........");
		Serial.write((uint8_t*)entry, sizeof(entry));
		delay(1000);
		slcd.setCursor(0,1);
		slcd.print("...........");
		//Serial.write((uint8_t*)signal, sizeof(signal[0].code));
		delay(1000);
		slcd.setCursor(0,1);
		slcd.print(".............");
		//Serial.write((uint8_t*)signal_entry, sizeof(signal_entry));
		delay(1000);
		slcd.setCursor(0,1);
		slcd.print("...............");
		slcd.clear();
		slcd.setCursor(0,1);
		slcd.print("Success");
		delay(1000);
		slcd.clear();
	}

	//show menu
	slcd.setCursor(0,0);
	slcd.print(menu[main_cursor]);
	if (status == 1) {
		slcd.setCursor(0,1);
		slcd.print(sub_menu[sub_cursor]);
	}
	if (digitalRead(buttonPin)) {
		if (status == 0) {
			status = 1;
			sub_cursor = entry[main_cursor];
		}
		else {
			//send signal[sub_cursor]
			//loadsignal
			myFile = SD.open("sig.txt", FILE_READ);
			if(myFile) {
				myFile.seek(sub_cursor*sizeof(signal[0].code));
				read_to_array(myFile, (uint8_t*)signal[0].code, sizeof(signal[0].code));
			}
			myFile.close();
			int count = signal[0].code[0];
			irsend.sendRaw(signal[0].code+1, count, 38);
		}
	} 
	else if (digitalRead(learnPin)) {
		if (status == 0) {
			// do nothing
		} else {
			// Listen for IR signal and write to file[sub_cursor]
			Serial.println("!!");
			if (irrecv.decode(&results)) {
				Serial.println("!!!");
				dump(&results);
				myFile = SD.open("sig.txt", FILE_WRITE);
				if(myFile) {
					//Serial.println("");
					myFile.seek(sub_cursor*sizeof(signal[0].code));
					myFile.write((uint8_t*)signal, sizeof(signal[0].code));
					Serial.println(signal[0].code[0]);
					for (int i = 1; i <= signal[0].code[0]; i++) {
						Serial.print(signal[0].code[i], DEC);
						Serial.print(" ");
					}
					Serial.println("");
				} else {
					Serial.println("error");
				}
				myFile.close();
				irrecv.resume(); // Receive the next value
			}
		}
	} else {
		if (status == 0) {
			if (menu[++main_cursor][0] =='\0') {
				main_cursor = 0;
			}
		} else {
			if (++sub_cursor >= entry[main_cursor+1]) {
				status = 0;
			}
		}
	}
	delay(1000);
	slcd.clear();
}

void dump(decode_results *results) {
	int count = results->rawlen;
	if (results->decode_type == UNKNOWN) {
		Serial.println("Unknown encoding: ");
	}
	signal[0].code[0] = count;
	for (int i = 1; i < count; i++) {
		signal[0].code[i] = results->rawbuf[i]*USECPERTICK;
	}
	signal[0].code[count] = results->rawbuf[0]*USECPERTICK;
}
