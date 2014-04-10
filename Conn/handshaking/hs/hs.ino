const char* menu[] = {"TV", "DVD", "AIR"};
const char* sub_menu[] = {"UP", "DOWN", "VUP", "UP", "DOWN", "OPEN", "CLOSE"};
int entry[] = {0, 3, 5, 7};
int signal[] = {1, 1, 2, 2, 2, 3, 3, 4, 4, 5, 7};
int signal_entry[] = {0, 2, 5, 7, 9, 10, 10, 11};

const int buttonPin = 8;     // the number of the pushbutton pin

// variables will change:
int buttonState = 0;         // variable for reading the pushbutton status
void printsig(const char* a[], int len);
void printsig_int(int a[], int len);

#define printsig(arr) printsig_impl(arr, sizeof(arr)/sizeof(*arr))
#define printsig_int(arr) printsig_int_impl(arr, sizeof(arr)/sizeof(*arr))

void setup() {
	// initialize the pushbutton pin as an input:
	pinMode(buttonPin, INPUT);
	// open the serial port at 9600 bps:
	Serial.begin(9600);
}

void loop() {
	// read the state of the pushbutton value:
	buttonState = digitalRead(buttonPin);

	// check if the pushbutton is pressed.
	// if it is, the buttonState is HIGH:
	if (buttonState == HIGH) {
		// print it out in many formats:
		//Serial.println(menu[i]);
		// delay 10 milliseconds before the next reading:
		printsig(menu);
		delay(1000);
		printsig(sub_menu);
		delay(1000);
		printsig_int(entry);
		delay(1000);
		printsig_int(signal);
		delay(1000);
		printsig_int(signal_entry);
		delay(1000);
	}
	else {
		// turn LED off:
	}
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
