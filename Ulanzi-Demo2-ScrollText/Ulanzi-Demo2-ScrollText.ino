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

// Another font from PixelIt that is narrower and therefore less Space needs:
// https://github.com/aptonline/PixelIt_Ulanzi/blob/main/src/PixelIt.ino
#include "PixelItFont.h"

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

// The text to be displayed
char* text = "Today is a beautiful day.";


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

  // Select the narrow font
  matrix->setFont(&PixelItFont);
  
  // Clear everything on display:
  matrix->clear();
  
  // Set start position for the text.
  // Important: Since we use a different font, the start position must
  // be set to (0,7), i.e. bottom left:
  matrix->setCursor(0, 7);
  
  // Output text.
  matrix->print(text);

  // Show all. Important: If you forget this, nothing will be displayed.
  matrix->show();

  // Wait a second, then the scrolling message starts
  delay(1000);

  // other text color for the tread to make it more interesting:
  matrix->setTextColor(matrix->Color(51, 255, 153));

}
//-----------------------------------------------------------------------------------------
// Calculate how many pixels of the transferred text is wide.
// The function is not entirely, it seems as if always a couple
// pixel more to be returned than the text is wide. But doesn't do anything.
uint16_t textWidth(char* text)
{
  // The function "Getteextbounds ()" expects a few variables that you will fill
  // (Therefore, the addresses of the variables are transferred, otherwise
  // We are only interested in the width
  int16_t ulx, uly;
  uint16_t width, height;
  matrix->getTextBounds(text, 0, 7, &ulx, &uly, &width, &height);
  return width;
}
//-----------------------------------------------------------------------------------------

void loop() {
  // starting position for the text: on the right edge of the display.
  // "Static" means that the variable only gets the value matrix_wreite the first time,
  // After that, this line has no function.
  static int x = MATRIX_WIDTH;

  // Width of the text in pixels:
  static int text_width_in_pixel = textWidth(text);

  // Clear Screen
  matrix->clear();
  
  // Set the current position, it is reduced by one with every run of Loop ().
  // This shows the text further and further on the left
  matrix->setCursor(x, 7);

  // output text and display:
  matrix->print(text);
  matrix->show();

  // The next round the text should be given a pixel further on the left. This comes the
  // head script effect
  x--;

  // When the text has run through completely, start right again (as at the beginning):
  if (x < -text_width_in_pixel)
  {
    x = MATRIX_WIDTH;
  }

  // short break (100 ms) so that the text does not rush too quickly:
  delay(100);
  
}
