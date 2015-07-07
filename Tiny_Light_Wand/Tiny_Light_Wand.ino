#include <Bounce2.h>

#include <Adafruit_NeoPixel.h>

#define NUM_PIX 50

Adafruit_NeoPixel strip = Adafruit_NeoPixel(NUM_PIX, 0, NEO_GRB + NEO_KHZ800);

Bounce debouncer = Bounce();

byte pixel = 0;
bool dir = true;
byte cur_prog = 0;

byte brightness = 254;

unsigned long fadeTime = 80; //time it takes to move to next LED in millis()
unsigned long loopTime = NUM_PIX * fadeTime; //loop is based on how many leds, it all directions make sure you dont get an index out of bounds
byte LEDbrightness[NUM_PIX]; //keeps the LEDS brightness value, is checked over consitently in a loop
byte LEDState[NUM_PIX]; //array to let it know if it should be getting brighter or dimmer

color curColor, curColor2;

/** ^^
 * Global Variables
**/

color white = {255, 255, 255};
color red = {255, 0, 0};
color orange = {255, 128, 0};
color yellow = {255, 255, 0};
color lime = {128, 255, 0};
color green = {0, 255, 0};
color turqoise = {0, 255, 128};
color cyan = {0, 255, 255};
color lightBlue = {0, 128, 255};
color blue = {0, 0, 255};
color black = {0, 0, 0};
color pink = {255, 0, 128};
color purple = {255, 0, 255};
color magenta = {128, 0, 255};

void setup() {
  pinMode(4, INPUT_PULLUP);

  debouncer.attach(4);
  debouncer.interval(5);

  strip.begin();
  strip.setBrightness(50);
  for (byte i = 0; i < NUM_PIX; i++) {
    strip.setPixelColor(i, 0, 0, 0);
  }
  america();
  strip.show();
}

void loop() {
  debouncer.update();

  switch (cur_prog % 13) {
    case 0:
      america();
      break;
    case 1:
      rainbow();
      break;
    case 2:
      mexico();
      break;
    case 3:
      france();
      break;
    case 4:
      glow();
      break;
    case 5:
      chase();
      break;
    case 6:
      pong();
      break;
    case 7:
      two_pong();
      break;
    case 8:
      split();
      break;
    case 9:
      fades();
      break;
    case 10:
      burst();
      break;
    case 11:
      blend();
      break;
    case 12:
      pulse();
      break;
    default:
      break;
  }
  strip.show();
  if ( debouncer.fell()) {
    cur_prog++;
    pixel = 0;
    dir = true;
    curColor = white;
  }
}

void america() {
  byte pixel_num = 0;
  for (byte i = 0; i < 20; i++) {
    strip.setPixelColor(pixel_num++, blue);
  }
  for (byte j = 0; j < 5 ; j++) {
    for (byte i = 0; i < 3; i++) {
      strip.setPixelColor(pixel_num++, white);
    }
    for (byte i = 0; i < 3; i++) {
      strip.setPixelColor(pixel_num++, red);
    }
  }
}

void chase() {
  if (pixel == NUM_PIX + 1) {
    pixel = 0;
    curColor = newColor();
  }
  color c;
  for (byte i = 0; i < NUM_PIX; i++) {
    c = black;
    if (abs(i - pixel) < 3) {
      c = curColor;
    }
    strip.setPixelColor(i, c);
  }
  pixel = pixel + 1;
  delay(20);
}

void pong() {
  //bytes roll over to 255 instead of negative numbers
  if (pixel == NUM_PIX + 1 || pixel == 255) {
    dir = !dir;
    curColor = newColor();
  }
  color c;
  for (byte i = 0; i < NUM_PIX; i++) {
    c = black;
    if (abs(i - pixel) < 3) {
      c = curColor;
    }
    strip.setPixelColor(i, c);
  }
  pixel = dir ? pixel + 1 : pixel - 1 ;
  delay(20);
}

void two_pong() {
  if (pixel == NUM_PIX + 1 || pixel == 255) {
    dir = !dir;
    curColor = newColor();
    curColor2 = newColor();
  }
  color c;
  for (byte i = 0; i < NUM_PIX; i++) {
    c = black;
    if (abs(i - pixel) < 3) {
      c = curColor;
    }
    if (abs(i - (NUM_PIX - pixel)) < 3) {
      c = curColor2;
    }
    strip.setPixelColor(i, c);
  }
  pixel = dir ? pixel + 1 : pixel - 1 ;
  delay(20);
  //delay(analogRead(A0) / 10);
}

void split() {
  if (pixel == NUM_PIX + 1) {
    pixel = NUM_PIX / 2;
    curColor = newColor();
    curColor2 = newColor();
  }
  color c;
  for (byte i = 0; i < NUM_PIX; i++) {
    c = black;
    if (abs(i - pixel) < 3) {
      c = curColor;
    }
    if (abs(i - (NUM_PIX - pixel)) < 3) {
      c = curColor2;
    }
    strip.setPixelColor(i, c);
  }
  pixel++;
  delay(20);
  //delay(analogRead(A0) / 10);
}

void fades() {
  unsigned long timer = millis() % loopTime;

  pixel = timer / fadeTime;
  LEDState[pixel] = 1;
  LEDState[(pixel + 25) % 49] = 1;

  for (byte i = 0; i < NUM_PIX; i++) {
    if (LEDbrightness[i] > 254) {
      LEDState[i] = 2;
    }
    if (LEDState[i] == 1) {
      LEDbrightness[i]++;
    }
    if (LEDState[i] == 2) {
      LEDbrightness[i]--;
    }
    if (LEDbrightness[i] == 0) {
      LEDState[i] = 0;
      LEDbrightness[i] = 0;
    }
  }

  for (byte i = 0; i < NUM_PIX; i++) {
    strip.setPixelColor(i, LEDbrightness[i], 0, 0);
  }
}

void burst() {
  unsigned long timer = millis() % (loopTime / 2);

  pixel = timer / fadeTime;
  LEDState[pixel + NUM_PIX / 2] = 1;
  LEDState[NUM_PIX - (pixel + NUM_PIX / 2)] = 1;

  for (byte i = 0; i < NUM_PIX; i++) {
    if (LEDbrightness[i] > 254) {
      LEDState[i] = 2;
    }
    if (LEDState[i] == 1) {
      LEDbrightness[i]++;
    }
    if (LEDState[i] == 2) {
      LEDbrightness[i]--;
    }
    if (LEDbrightness[i] == 0) {
      LEDState[i] = 0;
      LEDbrightness[i] = 0;
    }
  }

  for (byte i = 0; i < NUM_PIX; i++) {
    strip.setPixelColor(i, LEDbrightness[i], 0, 0);
  }
}

void glow() {
  if (brightness == 255 || brightness == 0) {
    dir = !dir;
  }
  color c;
  for (int i = 0; i < NUM_PIX; i++) {
    c.r = brightness;
    c.g = 0;
    c.b = 0;
    strip.setPixelColor(i, c);
  }
  brightness = dir ? brightness - 1 : brightness + 1 ;
  delay(5);
  //delay(analogRead(A0) / 10);
}

void mexico() {
  byte pixel_num = 0;
  for (byte i = 0; i < 16; i++) {
    strip.setPixelColor(pixel_num++, green);
  }
  for (byte i = 0; i < 16; i++) {
    strip.setPixelColor(pixel_num++, white);
  }
  for (byte i = 0; i < 17; i++) {
    strip.setPixelColor(pixel_num++, red);
  }
}

void rainbow() {
  byte pixel_num = 0;
  for (byte i = 0; i < 8; i++) {
    strip.setPixelColor(pixel_num++, red);
  }
  for (byte i = 0; i < 8; i++) {
    strip.setPixelColor(pixel_num++, orange);
  }
  for (byte i = 0; i < 8; i++) {
    strip.setPixelColor(pixel_num++, yellow);
  }
  for (byte i = 0; i < 8; i++) {
    strip.setPixelColor(pixel_num++, green);
  }
  for (byte i = 0; i < 8; i++) {
    strip.setPixelColor(pixel_num++, blue);
  }
  for (byte i = 0; i < 9; i++) {
    strip.setPixelColor(pixel_num++, purple);
  }
}

void france() {
  byte pixel_num = 0;
  for (byte i = 0; i < 16; i++) {
    strip.setPixelColor(pixel_num++, red);
  }
  for (byte i = 0; i < 16; i++) {
    strip.setPixelColor(pixel_num++, white);
  }
  for (byte i = 0; i < 17; i++) {
    strip.setPixelColor(pixel_num++, blue);
  }
}

void blend() {
  unsigned long timer = millis() % loopTime;

  pixel = timer / fadeTime;
  LEDState[pixel] = 1;
  LEDState[(pixel + 25) % 49] = 1;

  for (byte i = 0; i < NUM_PIX; i++) {
    if (LEDbrightness[i] > 254) {
      LEDState[i] = 2;
    }
    if (LEDState[i] == 1) {
      LEDbrightness[i]++;
    }
    if (LEDState[i] == 2) {
      LEDbrightness[i]--;
    }
    if (LEDbrightness[i] == 0) {
      LEDState[i] = 0;
      LEDbrightness[i] = 0;
    }
  }

  for (byte i = 0; i < NUM_PIX; i++) {
    strip.setPixelColor(i, LEDbrightness[i], 0, 255 - LEDbrightness[i]);
  }
}

void pulse() {
  unsigned long timer = millis() % (loopTime / 4);

  byte half = NUM_PIX / 2;
  byte q1 = half / 2;
  byte q3 = half + q1;

  pixel = timer / fadeTime;
  color c;
  for (byte i = 0; i < NUM_PIX; i++) {
    c = white;
    if (abs(pixel - i) < 3) {
      c = cyan;
    }
    if (abs(NUM_PIX - (pixel + i)) < 3) {
      c = cyan;
    }
    if (abs(i - half - pixel) < 3) {
      c = cyan;
    }
    if (abs(i - q1 - pixel) < 3) {
      c = cyan;
    }
    if (abs(i - q3 - pixel) < 3) {
      c = cyan;
    }
    if (abs(i - half + pixel) < 3) {
      c = cyan;
    }
    if (abs(i - q1 + pixel) < 3) {
      c = cyan;
    }
    if (abs(i - q3 + pixel) < 3) {
      c = cyan;
    }
    strip.setPixelColor(i, c);
  }
}

color newColor() {
  switch (random(13)) {
    case 0:
      return white;
      break;
    case 1:
      return red;
      break;
    case 2:
      return orange;
      break;
    case 3:
      return yellow;
      break;
    case 4:
      return lime;
      break;
    case 5:
      return green;
      break;
    case 6:
      return turqoise;
      break;
    case 7:
      return cyan;
      break;
    case 8:
      return lightBlue;
      break;
    case 9:
      return blue;
      break;
    case 10:
      return magenta;
      break;
    case 11:
      return purple;
      break;
    case 12:
      return pink;
      break;
    default:
      break;
  }
}