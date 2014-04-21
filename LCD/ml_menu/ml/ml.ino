#include <SoftwareSerial.h>
#include <IRremote.h>
#include <SerialLCD.h>
#include <string>
#include <SD.h>

File myFile;
char inbyte;
String indata="";
int buttonPin = 9;
int uploadPin = 6;
int RECV_PIN = 11;
SerialLCD slcd(7,8);
IRsend irsend;
int i = 0;
int sub_count = 0;
int sub_start = 0;

//char menu[5][10] = {"TV", "DVD", "AIR", ""};
//char sub_menu[20][10] = {"UP", "DOWN", "VUP", "UP", "DOWN", "OPEN", "CLOSE"};
//int entry[] = {0, 3, 5, 7};
//int signal[] = {1, 1, 2, 2, 2, 3, 3, 4, 4, 5, 7};
//int signal_entry[] = {0, 2, 5, 7, 9, 10, 10, 11};

char menu[5][10];
char sub_menu[20][10];
int entry[4];
int signal[11];
int signal_entry[8];

int buttonState = 0;         // variable for reading the pushbutton status

//void printsig(const uint8_t* a[], int len);
//void printsig_int(int a[], int len);
//#define printsig(arr) printsig_impl(arr, sizeof(arr)/sizeof(*arr))
//#define printsig_int(arr) printsig_int_impl(arr, sizeof(arr)/sizeof(*arr))

#define read_to_array(file, arr) \
{\
	int i;\
	for (i = 0; i < sizeof(arr); i++) {\
		if ((((uint8_t*)arr)[i] = file.read()) == -1) {\
			Serial.println("a byte is expected but failed");\
		}\
	}\
}

//if ((((uint8_t*)arr)[i] = file.read()) == -1) {

void setup() {
	Serial.begin(9600);
	slcd.begin();
	pinMode(buttonPin,INPUT);
	slcd.backlight();
	pinMode(10, OUTPUT);
	//slcd.print("Hello, world");
	//delay(1000);
	if (!SD.begin(4)) {
		Serial.println("initialization failed!");
		return;
	}
	myFile = SD.open("conf.txt");
	if (myFile) {
		Serial.println("reading conf.txt");
		read_to_array(myFile, menu);
		read_to_array(myFile, sub_menu);
		read_to_array(myFile, entry);
		read_to_array(myFile, signal);
		read_to_array(myFile, signal_entry);
		Serial.println("read finished");
		myFile.close();
		for (int k = 0; k < sizeof(menu); k++) {
			Serial.println(menu[k]);
			//why print out sub_menu
		}
	} else {
		// if the file didn't open, print an error:
		Serial.println("error opening test.txt");
	}
}

//add number before
//int add(int n)
//{
//	int sum=0;
//	for (int i=0; i<n; i++) {
//		sum	= sum + menu_count[i];
//	}
//	return sum;
//}

int status = 0; // 0 for main menu; 1 for sub menu; 
int main_cursor = 0;
int sub_cursor = 0;

void loop()
{
	// upload
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
		Serial.write((uint8_t*)signal, sizeof(signal));
		delay(1000);
		slcd.setCursor(0,1);
		slcd.print(".............");
		Serial.write((uint8_t*)signal_entry, sizeof(signal_entry));
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
	delay(1000);
	if (digitalRead(buttonPin)) {
		if (status == 0) {
			status = 1;
			sub_cursor = entry[main_cursor];
		} else {
			int idx = signal_entry[sub_cursor];
			while (idx < signal_entry[sub_cursor+1]) {
				// send signal[idx];
				slcd.print("sent");
				idx++;
			}
		}
	} else {
		if (status == 0) {
			if (menu[++main_cursor][0] == '\0'  ) {
				main_cursor = 0;
			}
		} else {
			if (++sub_cursor >= entry[main_cursor+1]) {
				status = 0;
			}
		}
	}
	slcd.clear();
}
