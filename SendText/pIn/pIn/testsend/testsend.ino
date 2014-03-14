int i = 0;
void setup() {
  Serial.begin(9600);  
}
 
void loop() {
  Serial.write(5);
  Serial.write(4);
  Serial.write(3);
  Serial.write(2);
}
