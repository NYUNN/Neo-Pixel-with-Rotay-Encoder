// Wood lamp has a white light indicatior. Also, the other part change colors according to angle. The brightness is depending of the volume of the music.
// Metal lamp has the same effect as wood lamp.
// Acrylic lamp only has a white light indicator.
// When two or three indicators meet each other, that two or three lamps start to bling.

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

// Encoder connect to digitalpin 2 and 3 on the Arduino.
volatile unsigned int counter = 0; //This variable will increase or decrease depending on the rotation of encoder

int previous = 0;
int f = 0;


void setup() {
  woodLamp.begin();
  metalLamp.begin();
  arcylicLamp.begin();

  Serial.begin(9600);

  //Setting up interrupt
  //A rising pulse from encodenren activated ai0(). AttachInterrupt 0 is DigitalPin nr 2 on moust Arduino.
  attachInterrupt(0, ai0, RISING);

  //B rising pulse from encodenren activated ai1(). AttachInterrupt 1 is DigitalPin nr 3 on moust Arduino.
  attachInterrupt(1, ai1, RISING);
}

void loop() {
  int potValue1 = analogRead(A0);
  int potValue2 = analogRead(A1);

  int color1 = map(potValue1, 0, 1024, 0, 6);
  int color2 = map(potValue2, 0, 1024, 0, 6);
  int k = map(potValue2, 0, 1023, 0, 28);

  int current = map(counter, 0, 65535, 0, 2000);
  int l = current - previous;

  // brightness for the lamps
  int b1 = 10;
  int b2 = 10;
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
  Serial.println(f);

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

  previous = current;

  // metal lamp
  for (int n = k; n < NUMPIXEL2; n++) {
    metalLamp.setPixelColor(n, metalLamp.Color(b2, b2, b2));
    metalLamp.show();
  }

  for (int m = 0; m < k; m++) {
    if (color2 == 0) {
      metalLamp.setPixelColor(m, metalLamp.Color(0, b1 / 5 * 0 , b1 / 5 * 5));
    } else if (color2 == 1) {
      metalLamp.setPixelColor(m, metalLamp.Color(0, b1 / 5 * 1 , b1 / 5 * 4));
    } else if (color2 == 2) {
      metalLamp.setPixelColor(m, metalLamp.Color(0, b1 / 5 * 2 , b1 / 5 * 3));
    } else if (color2 == 3) {
      metalLamp.setPixelColor(m, metalLamp.Color(0, b1 / 5 * 3 , b1 / 5 * 2));
    } else if (color2 == 4) {
      metalLamp.setPixelColor(m, metalLamp.Color(0, b1 / 5 * 4 , b1 / 5 * 1));
    } else {
      metalLamp.setPixelColor(m, metalLamp.Color(0, b1 / 5 * 5 , b1 / 5 * 0));
    }
    metalLamp.show();
  }

  for (int g = k + 3; g < NUMPIXEL2; g++) {
    if (color2 == 0) {
      metalLamp.setPixelColor(g, metalLamp.Color(0, b1 / 5 * 0 , b1 / 5 * 5));
    } else if (color2 == 1) {
      metalLamp.setPixelColor(g, metalLamp.Color(0, b1 / 5 * 1 , b1 / 5 * 4));
    } else if (color2 == 2) {
      metalLamp.setPixelColor(g, metalLamp.Color(0, b1 / 5 * 2 , b1 / 5 * 3));
    } else if (color2 == 3) {
      metalLamp.setPixelColor(g, metalLamp.Color(0, b1 / 5 * 3 , b1 / 5 * 2));
    } else if (color2 == 4) {
      metalLamp.setPixelColor(g, metalLamp.Color(0, b1 / 5 * 4 , b1 / 5 * 1));
    } else {
      metalLamp.setPixelColor(g, metalLamp.Color(0, b1 / 5 * 5 , b1 / 5 * 0));
    }
    metalLamp.show();
  }

  // wood lamp
  for (int i = 0; i < 3; i++) {
    woodLamp.setPixelColor(i, woodLamp.Color(b1, b1, b1));
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


  delay(10);
}


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







