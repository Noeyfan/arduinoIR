#include <SoftwareSerial.h>
#include <IRremote.h>
#include <SerialLCD.h>
#include <string>

char inbyte;
String indata="";
int buttonPin = 9;
int downloadPin = 6;
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
				slcd.print();
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
	//while (menu[i] != NULL) {
	//	slcd.setCursor(0,0);
	//	slcd.print(menu[i++]);
	//	delay(1000);
	//	if (digitalRead(buttonPin)) {
	//		sub_count = menu_count[i];
	//		sub_start = add(i);
	//		Serial.println(sub_count);
	//		Serial.println(sub_start);
	//		while(j < sub_count) {
	//			slcd.setCursor(0,1);
	//			slcd.print(sub_menu[sub_start]);
	//			delay(1000);
	//			if (digitalRead(buttonPin)) {
	//				//send signal[sub_start];
	//			}
	//			sub_start++;
	//			j++;
	//		}
	//		j=0;
	//		slcd.clear();
	//	} else {
	//		i++;
	//	}
	//}
	//i=0;
	//slcd.clear();
}
