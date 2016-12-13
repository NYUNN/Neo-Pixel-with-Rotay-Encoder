#include <Adafruit_NeoPixel.h>
#ifdef __AVR__
#include <avr/power.h>
#endif

#define PIN1            13 // wood
#define PIN2            12 // acrylic
#define PIN3            11 // metal

#define NUMPIXEL1       36 // wood
#define NUMPIXEL2       40 // acrylic
#define NUMPIXEL3       16 // metal

Adafruit_NeoPixel woodLamp = Adafruit_NeoPixel(NUMPIXEL1, PIN1, NEO_GRB + NEO_KHZ800);
Adafruit_NeoPixel acrylicLamp = Adafruit_NeoPixel(NUMPIXEL2, PIN2, NEO_GRB + NEO_KHZ800);
Adafruit_NeoPixel metalLamp = Adafruit_NeoPixel(NUMPIXEL3, PIN3, NEO_GRB + NEO_KHZ800);

// Encoder connect to digitalpin 2 and 3 on the Arduino.
volatile unsigned int counter = 0; //This variable will increase or decrease depending on the rotation of encoder

// Variables to control lighting in metal lamp
int current = 0;
int previous = 0;
int difference = 0;
int index = 0;

// Byte sent fron MAXMSP
int maxData = 0;

void setup() {
  woodLamp.begin();
  acrylicLamp.begin();
  metalLamp.begin();

  Serial.begin(9600);

  // Setting up interrupt
  // A rising pulse from encodenren activated ai0(). AttachInterrupt 0 is DigitalPin nr 2 on moust Arduino.
  attachInterrupt(0, ai0, RISING);

  // B rising pulse from encodenren activated ai1(). AttachInterrupt 1 is DigitalPin nr 3 on moust Arduino.
  attachInterrupt(1, ai1, RISING);
}

void loop() {

  while (Serial.available() > 0) {
    maxData = Serial.read();
  }

  // brightness for neopixel
  int b1 = maxData; // wood
  int b2 = maxData; // acrylic
  int b3 = 100; // metal

  int woodPot = analogRead(A0);
  int arylicPot = analogRead(A1);

  int woodCol = map(woodPot, 0, 1024, 0, 6);
  int arylicCol = map(arylicPot, 0, 1024, 0, 6);

  current = map(counter, 0, 65535, 0, 1000);
  difference = current - previous;
  previous = current;

  // send data to MAXMSP
  int encoderValue = map(counter, 0, 65535, 0, 1023);
  Serial.print(woodCol, DEC);
  Serial.print(" ");
  Serial.print(arylicCol, DEC);
  Serial.print(" ");
  Serial.println(encoderValue);


  // lighting for the wood lamp
  for (int i = 0; i < 3; i++) {
    woodLamp.setPixelColor(i, woodLamp.Color(100, 100, 100));
    woodLamp.show();
  }
  for (int i = 3; i < NUMPIXEL1; i++) {
    if (woodCol == 0) {
      woodLamp.setPixelColor(i, woodLamp.Color(0, b1 / 5 * 5, b1 / 5 * 0));
    } else if (woodCol == 1) {
      woodLamp.setPixelColor(i, woodLamp.Color(0, b1 / 5 * 3, b1 / 5 * 2));
    } else if (woodCol == 2) {
      woodLamp.setPixelColor(i, woodLamp.Color(0, b1 / 5 * 1, b1 / 5 * 4));
    } else if (woodCol == 3) {
      woodLamp.setPixelColor(i, woodLamp.Color(0, b1 / 5 * 0, b1 / 5 * 5));
    } else if (woodCol == 4) {
      woodLamp.setPixelColor(i, woodLamp.Color(0, b1 / 5 * 2, b1 / 5 * 3));
    } else {
      woodLamp.setPixelColor(i, woodLamp.Color(0, b1 / 5 * 4, b1 / 5 * 1));
    }
    woodLamp.show();
  }


  // lighting for the acrylic lamp
  int k = map(arylicPot, 0, 1023, 0, NUMPIXEL2 - 2);
  for (int i = k; i < k + 3; i++) {
    acrylicLamp.setPixelColor(i, acrylicLamp.Color(100, 100, 100));
    acrylicLamp.show();
  }
  for (int i = 0; i < k; i++) {
    if (arylicCol == 0) {
      acrylicLamp.setPixelColor(i, acrylicLamp.Color(b2 / 5 * 5, 0, b2));
    } else if (arylicCol == 1) {
      acrylicLamp.setPixelColor(i, acrylicLamp.Color(b2 / 5 * 3, 0, b2));
    } else if (arylicCol == 2) {
      acrylicLamp.setPixelColor(i, acrylicLamp.Color(b2 / 5 * 1, 0, b2));
    } else if (arylicCol == 3) {
      acrylicLamp.setPixelColor(i, acrylicLamp.Color(b2 / 5 * 0, 0, b2));
    } else if (arylicCol == 4) {
      acrylicLamp.setPixelColor(i, acrylicLamp.Color(b2 / 5 * 2, 0, b2));
    } else {
      acrylicLamp.setPixelColor(i, acrylicLamp.Color(b2 / 5 * 4, 0, b2));
    }
    acrylicLamp.show();
  }
  for (int i = k + 3; i < NUMPIXEL2; i++) {
    if (arylicCol == 0) {
      acrylicLamp.setPixelColor(i, acrylicLamp.Color(b2 / 5 * 5, 0, b2));
    } else if (arylicCol == 1) {
      acrylicLamp.setPixelColor(i, acrylicLamp.Color(b2 / 5 * 3, 0, b2));
    } else if (arylicCol == 2) {
      acrylicLamp.setPixelColor(i, acrylicLamp.Color(b2 / 5 * 1, 0, b2));
    } else if (arylicCol == 3) {
      acrylicLamp.setPixelColor(i, acrylicLamp.Color(b2 / 5 * 0, 0, b2));
    } else if (arylicCol == 4) {
      acrylicLamp.setPixelColor(i, acrylicLamp.Color(b2 / 5 * 2, 0, b2));
    } else {
      acrylicLamp.setPixelColor(i, acrylicLamp.Color(b2 / 5 * 4, 0, b2));
    }
    acrylicLamp.show();
  }


  // lighting for the metal lamp
  if (difference > 0) {
    index ++;
    if (index > NUMPIXEL3 - 1) {
      index = 0;
    }
  } else if (difference < 0) {
    index--;
    if (index < 0) {
      index = 15;
    }
  }

  if (index == NUMPIXEL3 - 2) {
    for (int i = index; i < index + 2; i++) {
      metalLamp.setPixelColor(i, metalLamp.Color(b3, b3, b3));
      metalLamp.show();
    }
    metalLamp.setPixelColor(0, metalLamp.Color(b3, b3, b3));
    metalLamp.show();
    for (int i = 1; i < index; i++) {
      metalLamp.setPixelColor(i, metalLamp.Color(0, 0, 0));
      metalLamp.show();
    }
  } else if ( index == NUMPIXEL3 - 1) {
    metalLamp.setPixelColor(NUMPIXEL3 - 1, metalLamp.Color(b3, b3, b3));
    metalLamp.show();
    for (int i = 0; i < 2; i++) {
      metalLamp.setPixelColor(i, metalLamp.Color(b3, b3, b3));
      metalLamp.show();
    }
    for (int i = 2; i < index; i++) {
      metalLamp.setPixelColor(i, metalLamp.Color(0, 0, 0));
      metalLamp.show();
    }
  } else {
    for (int i = index; i < index + 3; i++) {
      metalLamp.setPixelColor(i, metalLamp.Color(b3, b3, b3));
      metalLamp.show();
    }
    for (int i = 0; i < index; i++) {
      metalLamp.setPixelColor(i, metalLamp.Color(0, 0, 0));
      metalLamp.show();
    }
    for (int i = index + 3; i < NUMPIXEL3; i++) {
      metalLamp.setPixelColor(i, metalLamp.Color(0, 0, 0));
      metalLamp.show();
    }
  }

  delay(10);
}


// Encoder
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


