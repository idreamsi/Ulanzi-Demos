// Demo program for the Ulanzi TC-001: Display of a small 8x8 icon

// Demo program for the Ulanzi TC001 that displays a Scroll Text

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

  // Clear Screen
  matrix->clear();
  
  // Show two graphics.
  // "Mario" and "Luigi" are from https://pixelit-project.github.io/pixelit/webui/#/gallery
  // Click the "i" in a circle to see the numbers for the graphic
  // You can design your own graphics here and then copy the numbers into our program:
  // https://pixelit-project.github.io/pixelit/webui/#/creator
  uint16_t icon1[64] {0,0,63650,63650,63650,63650,0,0,     // Pixel colors for the 1st line
                      0,0,63650,63650,63650,63488,63488,0, // 2. line
                      0,0,65139,25388,65139,25388,0,0,     // 3. Lines etc.
                      0,0,65139,65139,39296,39296,0,0,
                      65139,63488,12918,63488,63488,12918,63488,65139,
                      0,0,12918,12918,12918,12918,0,0,
                      0,0,12918,12918,12918,12918,0,0,
                      0,0,39296,0,0,39296,0,0};
  
  // All numbers in a long line here, that also works
  uint16_t icon2[64] {0,0,3745,3745,3745,3745,0,0,0,0,3745,3745,3745,3745,3745,0,0,0,65139,25388,65139,25388,0,0,0,0,65139,65139,39296,39296,0,0,65139,3745,12918,3745,3745,12918,3745,65139,0,0,12918,12918,12918,12918,0,0,0,0,12918,12918,12918,12918,0,0,0,0,39296,0,0,39296,0,0};
  
  // Show the first graphic at (0.0), i.e. on the far left.
  // The 8, 8 at the end means that the graphic has 8x8 pixels.
  matrix->drawRGBBitmap(0, 0, icon1, 8, 8);

  // The second graphic at X = 10, i.e. with 2 pixels distance to the first graphic
  matrix->drawRGBBitmap(10, 0, icon2, 8, 8);

  // Show Content
  matrix->show();
}

//--------------------------------------------------------------

void loop() {

}
