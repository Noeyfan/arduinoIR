int switchPin = 7;              // Switch connected to digital pin 7

void setup()                   
{
  Serial.begin(9600);           // set up Serial library at 9600 bps
  pinMode(switchPin, INPUT);    // sets the digital pin as input to read switch
}


void loop()                    
{
  Serial.print("Read switch input: ");
  Serial.println(digitalRead(switchPin));    // Read the pin and display the value,0 is switch off, 1 is switch on
  delay(1000);
}
