#include <Adafruit_NeoPixel.h>
#ifdef __AVR__
#include <avr/power.h>
#endif

#define PIN1            13
#define PIN2            12
#define PIN3            11

#define NUMPIXEL1       30
#define NUMPIXEL2       30
#define NUMPIXEL3       30

Adafruit_NeoPixel woodLamp = Adafruit_NeoPixel(NUMPIXEL1, PIN1, NEO_GRB + NEO_KHZ800);
Adafruit_NeoPixel metalLamp = Adafruit_NeoPixel(NUMPIXEL2, PIN2, NEO_GRB + NEO_KHZ800);
Adafruit_NeoPixel arcylicLamp = Adafruit_NeoPixel(NUMPIXEL3, PIN3, NEO_GRB + NEO_KHZ800);


int p1 = A0;
int p2 = A1;
int p1Value = 0;
int p2Value = 0;
int encoderValue;
volatile unsigned int counter = 0;  //This variable will increase or decrease depending on the rotation of encoder

int maxData = 0;            // byte sent from max

//Lighting variables
int previous = 0;
int f = 0;




void setup() {
  //Lighting
  woodLamp.begin();
  metalLamp.begin();
  arcylicLamp.begin();

  Serial.begin(9600);

  //Encoder: Setting up interrupt
  attachInterrupt(0, ai0, RISING);
  attachInterrupt(1, ai1, RISING);
}

void loop() {

  while (Serial.available() > 0) {
    maxData = Serial.read();
  }
  // put your main code here, to run repeatedly:
  p1Value = analogRead(p1);
  p2Value = analogRead(p2);

  int color1 = map(p1Value, 0, 1024, 0, 6);
  int color2 = map(p2Value, 0, 1024, 0, 6);
  int k = map(p2Value, 0, 1023, 0, 28);

  int current = map(counter, 0, 65535, 0, 2000);
  int l = current - previous;

  // brightness for the lamps
  int b1 = 10;
  int b2 = maxData;
  int b3 = 10;

  // arcylic lamp
  if (l > 0) {
    f ++;
    if (f > 29) {
      f = 0;
    }
  } else if (l < 0) {
    f--;
    if (f < 0) {
      f = 29;
    }
  }

  
  if (f == 28) {
    for (int p = f; p < f + 2; p++) {
      arcylicLamp.setPixelColor(p, arcylicLamp.Color(b3, b3, b3));
      arcylicLamp.show();
    }
    arcylicLamp.setPixelColor(0, arcylicLamp.Color(b3, b3, b3));
    arcylicLamp.show();

    for (int q = 1; q < f; q++) {
      arcylicLamp.setPixelColor(q, arcylicLamp.Color(0, 0, 0));
      arcylicLamp.show();
    }
  } else if ( f == 29) {
    arcylicLamp.setPixelColor(29, arcylicLamp.Color(b3, b3, b3));
    arcylicLamp.show();
    for (int q = 0; q < 2; q++) {
      arcylicLamp.setPixelColor(q, arcylicLamp.Color(b3, b3, b3));
      arcylicLamp.show();
    }
    for (int q = 2; q < f; q++) {
      arcylicLamp.setPixelColor(q, arcylicLamp.Color(0, 0, 0));
      arcylicLamp.show();
    }
  } else {
    for (int p = f; p < f + 3; p++) {
      arcylicLamp.setPixelColor(p, arcylicLamp.Color(b3, b3, b3));
      arcylicLamp.show();
    }

    for (int q = 0; q < f; q++) {
      arcylicLamp.setPixelColor(q, arcylicLamp.Color(0, 0, 0));
      arcylicLamp.show();
    }

    for (int s = f + 3; s < NUMPIXEL3; s++) {
      arcylicLamp.setPixelColor(s, arcylicLamp.Color(0, 0, 0));
      arcylicLamp.show();
    }
  }

  previous = current;

  // metal lamp
  for (int n = k; n < k + 3; n++) {
    metalLamp.setPixelColor(n, metalLamp.Color(100, 100, 100));
    metalLamp.show();
  }

  for (int m = 0; m < k; m++) {
    if (color2 == 0) {
      metalLamp.setPixelColor(m, metalLamp.Color(0, b2 / 5 * 0 , b2 / 5 * 5));
    } else if (color2 == 1) {
      metalLamp.setPixelColor(m, metalLamp.Color(0, b2 / 5 * 1 , b2 / 5 * 4));
    } else if (color2 == 2) {
      metalLamp.setPixelColor(m, metalLamp.Color(0, b2 / 5 * 2 , b2 / 5 * 3));
    } else if (color2 == 3) {
      metalLamp.setPixelColor(m, metalLamp.Color(0, b2 / 5 * 3 , b2 / 5 * 2));
    } else if (color2 == 4) {
      metalLamp.setPixelColor(m, metalLamp.Color(0, b2 / 5 * 4 , b2 / 5 * 1));
    } else {
      metalLamp.setPixelColor(m, metalLamp.Color(0, b2 / 5 * 5 , b2 / 5 * 0));
    }
    metalLamp.show();
  }

  for (int g = k + 3; g < NUMPIXEL2; g++) {
    if (color2 == 0) {
      metalLamp.setPixelColor(g, metalLamp.Color(0, b2 / 5 * 0 , b2 / 5 * 5));
    } else if (color2 == 1) {
      metalLamp.setPixelColor(g, metalLamp.Color(0, b2 / 5 * 1 , b2 / 5 * 4));
    } else if (color2 == 2) {
      metalLamp.setPixelColor(g, metalLamp.Color(0, b2 / 5 * 2 , b2 / 5 * 3));
    } else if (color2 == 3) {
      metalLamp.setPixelColor(g, metalLamp.Color(0, b2 / 5 * 3 , b2 / 5 * 2));
    } else if (color2 == 4) {
      metalLamp.setPixelColor(g, metalLamp.Color(0, b2 / 5 * 4 , b2 / 5 * 1));
    } else {
      metalLamp.setPixelColor(g, metalLamp.Color(0, b2 / 5 * 5 , b2 / 5 * 0));
    }
    metalLamp.show();
  }

  // wood lamp
  for (int i = 0; i < 3; i++) {
    woodLamp.setPixelColor(i, woodLamp.Color(100, 100, 100));
    woodLamp.show();
  }

  for (int j = 3; j < NUMPIXEL1; j++) {
    if (color1 == 0) {
      woodLamp.setPixelColor(j, woodLamp.Color(b1 / 5 * 5, b1 / 5 * 5 , 0));
    } else if (color1 == 1) {
      woodLamp.setPixelColor(j, woodLamp.Color(b1 / 5 * 4, b1 / 5 * 5 , 0));
    } else if (color1 == 2) {
      woodLamp.setPixelColor(j, woodLamp.Color(b1 / 5 * 3, b1 / 5 * 5 , 0));
    } else if (color1 == 3) {
      woodLamp.setPixelColor(j, woodLamp.Color(b1 / 5 * 2, b1 / 5 * 5 , 0));
    } else if (color1 == 4) {
      woodLamp.setPixelColor(j, woodLamp.Color(b1 / 5 * 1, b1 / 5 * 5 , 0));
    } else {
      woodLamp.setPixelColor(j, woodLamp.Color(b1 / 5 * 0, b1 / 5 * 5 , 0));
    }
    woodLamp.show();
  }


  encoderValue = map(counter, 0, 65535, 0, 1023);
  Serial.print(p1Value, DEC);
  Serial.print(" ");
  Serial.print(p2Value, DEC);
  Serial.print(" ");
  Serial.print(encoderValue, DEC);
  Serial.print(" ");
  Serial.print("\r");
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
