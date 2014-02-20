#include <SoftwareSerial.h>
#include <SerialLCD.h>

SerialLCD slcd(5,6,3);

void setup() {
//set up the LCD's number of columns and rows
slcd.begin(5,3);
//print a message to the lcd.
slcd.print("sucess");

}

void loop()
{
 slcd.backlight();
 slcd.setCursor(0,0);
 slcd.print(" lty ");
 slcd.setCursor(0,1);
 slcd.print(" syh ");
 slcd.setCursor(5,6);
 slcd.print(" yf ");
 slcd.setCursor(5,4);
 slcd.print("cs");


}
