#include <SoftwareSerial.h>
#include <IRremote.h>
#include <SerialLCD.h>
#include <string>

char inbyte;
String indata="";
int buttonPin = 9;
int uploadPin = 6;
int RECV_PIN = 11;
SerialLCD slcd(11,12);
IRsend irsend;
int i = 0;
int sub_count = 0;
int sub_start = 0;


const char* menu[] = {"TV", "DVD", "AIR"};
const char* sub_menu[] = {"UP", "DOWN", "VUP", "UP", "DOWN", "OPEN", "CLOSE"};
int entry[] = {0, 3, 5, 7};
int signal[] = {1, 1, 2, 2, 2, 3, 3, 4, 4, 5, 7};
int signal_entry[] = {0, 2, 5, 7, 9, 10, 10, 11};

int buttonState = 0;         // variable for reading the pushbutton status
//void printsig(const char* a[], int len);
//void printsig_int(int a[], int len);
#define printsig(arr) printsig_impl(arr, sizeof(arr)/sizeof(*arr))
#define printsig_int(arr) printsig_int_impl(arr, sizeof(arr)/sizeof(*arr))

void setup() {
	Serial.begin(9600);
	slcd.begin();
	pinMode(buttonPin,INPUT);
	slcd.backlight();
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
		printsig(menu);
		delay(1000);
		slcd.setCursor(0,1);
		slcd.print("....");
		printsig(sub_menu);
		delay(1000);
		slcd.setCursor(0,1);
		slcd.print("........");
		printsig_int(entry);
		delay(1000);
		slcd.setCursor(0,1);
		slcd.print("...........");
		printsig_int(signal);
		delay(1000);
		slcd.setCursor(0,1);
		slcd.print(".............");
		printsig_int(signal_entry);
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
			if (++main_cursor >= sizeof(menu)/sizeof(*menu)) {
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

void printsig_impl(const char* a[], int len) {
	for (int i = 0; i < len; i++) {
		Serial.print(a[i]);
		Serial.print(", ");
	}
	Serial.println("");
}

void printsig_int_impl(int a[], int len) {
	for (int i = 0; i < len; i++) {
		Serial.print(a[i]);
		Serial.print(", ");
	}
	Serial.println("");
}
