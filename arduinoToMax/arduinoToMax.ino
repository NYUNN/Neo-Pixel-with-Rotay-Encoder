int p1 = A0;
int p2 = A1;
int p1Value = 0;
int p2Value = 0;
void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
}

void loop() {
  // put your main code here, to run repeatedly:
  p1Value = analogRead(p1);
  p2Value = analogRead(p2);


  Serial.print(p1Value, DEC);
  Serial.print(" ");
  Serial.print(p2Value, DEC);
  Serial.print(" ");
  Serial.print("\r");
  delay(10);


}
