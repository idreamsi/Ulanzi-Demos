// Demo program that displays a text and a line on the Ulanzi TC-001.

// Board Manager:  "ESP32" (from "Expressif Systems")
//
// Library Manager: "FastLED NeoMatrix" (from Marc Merlin)
//
// Settings:
// Board: ESP32 Dev Module
// Upload Speed: 230400
// CPU Frequency: 240 MHz (WiFi/BT)
// Flash Frequency: 80 MHz
// Flash Mode: QIO
// Flash Size: 4 MB (32Mb)
// Partition Scheme: Default 4 MB with spiffs (1.2 MB APP/1.5 MB SPIFFS)
// Core Debug Level: None
// PSRAM: Disabled
// Port: for me /dev/cu.usbserial-2210, but it may be different for you
// If flashing fails, just try more often. If it doesn't work at all,
// Sometimes it helps to turn the display off and on again.

#include <Arduino.h>

// Function libraries for the LED display.
// The actual functions that you call yourself are in
// Adafruit_GFX, which is included by the two libraries.
// Anleitung dazu: https://learn.adafruit.com/adafruit-gfx-graphics-library
// All functions at a glance:
// https://github.com/adafruit/Adafruit-GFX-Library/blob/master/Adafruit_GFX.h
#include <FastLED_NeoMatrix.h>
#include <FastLED.h>

// Which pin the LEDs are connected to:
#define MATRIX_PIN 32

// There is a BUZZER on pin 15 that is too quiet and is otherwise not very useful.
#define BUZZER_PIN 15

// Number of LEDs in width and height:
#define MATRIX_WIDTH 32
#define MATRIX_HEIGHT 8

// The LED matrix as an object:
CRGB leds[MATRIX_WIDTH * MATRIX_HEIGHT];
FastLED_NeoMatrix *matrix;


void setup() {
  // Mute BUZZER
  pinMode(BUZZER_PIN, OUTPUT);
  digitalWrite(15, LOW);
  
  // Initialize LED matrix:
  FastLED.addLeds<NEOPIXEL, MATRIX_PIN>(leds, MATRIX_WIDTH * MATRIX_HEIGHT);
  matrix = new FastLED_NeoMatrix(leds, MATRIX_WIDTH, MATRIX_HEIGHT,
     NEO_MATRIX_TOP + NEO_MATRIX_LEFT + NEO_MATRIX_ROWS + NEO_MATRIX_ZIGZAG);
  matrix->begin();

 // Brightness goes from 0-255, we take a medium value:
  matrix->setBrightness(155);

  // Set text color: Orange!
  // Here you can select colors and read the red/green/blue values:
  // https://www.rapidtables.org/de/web/color/RGB_Color.html
  matrix->setTextColor(matrix->Color(255, 128, 0));
  
  // If the text is too long, don't start a new line (the LED matrix
  // can only display one line)
  matrix->setTextWrap(false);
  
  // Clear everything on display:
  matrix->clear();

  // Set start position for the text.
  // (0, 0) means (x=0, y=0), which is top left. (31, 7) is the right one
  // bottom corner of the display.
  // Important: If you set a different font, you have to change the start position
  // set to (0,7), i.e. bottom left: matrix->setCursor(0, 7);
  matrix->setCursor(0, 0);
  
  // Output text. Not everything fits on the display.
  matrix->print("Hallihallo");

  // And draw another line across it from top left to bottom right.
  // The text was printed first, the line after. That's why the line is over
  // the text and hides it.
  matrix->drawLine(0, 0, 31, 7, matrix->Color(80, 200, 80));
  
  // Show all. Important: If you forget this, nothing will be displayed.
  matrix->show();
  
}

void loop() {
}
