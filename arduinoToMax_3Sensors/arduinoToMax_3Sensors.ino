int p1 = A0;
int p2 = A1;
int p1Value = 0;
int p2Value = 0;
int encoderValue;
volatile unsigned int counter = 0;  //This variable will increase or decrease depending on the rotation of encoder

void setup() {
  Serial.begin(9600);
  //Encoder: Setting up interrupt
  attachInterrupt(0, ai0, RISING);
  attachInterrupt(1, ai1, RISING);
  pinMode(5, OUTPUT);
}

void loop() {
  // put your main code here, to run repeatedly:
  p1Value = analogRead(p1);
  p2Value = analogRead(p2);
  encoderValue = map(counter, 0, 65535, 0, 1023);
  Serial.print(p1Value, DEC);
  Serial.print(" ");
  Serial.print(p2Value, DEC);
  Serial.print(" ");
  Serial.print(encoderValue, DEC);
  Serial.print(" ");
  Serial.print("\r");
  delay(10);
}


//Encoder
void ai0() {
  // ai0 is activated if DigitalPin nr 2 is going from LOW to HIGH
  // Check pin 3 to determine the direction
  if (digitalRead(3) == LOW) {
    counter++;
  } else {
    counter--;
  }
}

void ai1() {
  // ai0 is activated if DigitalPin nr 3 is going from LOW to HIGH
  // Check with pin 2 to determine the direction
  if (digitalRead(2) == LOW) {
    counter--;
  } else {
    counter++;
  }
}
