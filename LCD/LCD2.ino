#include <SoftwareSerial.h>
#include <SerialLCD.h>

SerialLCD slcd(5,6);

void setup()
{
slcd.begin();

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


}
