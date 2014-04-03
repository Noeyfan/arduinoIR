char val;
int last_button_value;

void setup()
{
	Serial.begin(9600);
	last_button_value = 0;
	establishConn();
}

void loop()
{
	int value = digitalRead(Button1);
	if (value != last_button_value) {
		if (value == 1) {
			send_push_signal();
		} else {
			send_pop_signal();
		}
	}
	last_button_value = value;

	//if (Serial.available() <= 0) {
		Serial.println("B");
		delay(300);
	//}
	//if (Serial.available() > 0) {
	//	val = Serial.read();
	//}

	//if (val == '1') {
	//	Serial.println("get 1");	
	//}else {
	//	Serial.println("hello");
	//	delay(50);
	//}
}
void establishConn() {
	while (Serial.available() <= 0) {
		delay(300);
	}
}
