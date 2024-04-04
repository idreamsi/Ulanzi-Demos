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
uint16_t textBreite(char* text)
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
  // Startposition fuer den Text: am rechten Rand der Anzeige.
  // "static" bedeutet, dass die Variable nur beim ersten mal den Wert MATRIX_BREITE bekommt,
  // danach hat diese Zeile keine Funktion mehr.
  static int x = MATRIX_BREITE;

  // Breite des Texts in Pixeln:
  static int text_breite_in_pixel = textBreite(text);

  // Alten Text loeschen
  matrix->clear();
  // Aktuelle Position setzen, sie wird bei jedem Durchlauf von loop() um eins verringert.
  // Dadurch wird der Text immer weiter links angezeigt
  matrix->setCursor(x, 7);

  // Text ausgeben und anzeigen:
  matrix->print(text);
  matrix->show();

  // Naechste Runde soll der Text einen Pixel weiter links ausgegeben werden. Dadurch kommt der
  // Laufschrift-Effekt zustande
  x--;

  // Wenn der Text ganz durchgelaufen ist, starte wieder ganz rechts (wie am Anfang):
  if (x < -text_breite_in_pixel)
  {
    x = MATRIX_BREITE;
  }

  // Kurze Pause (100 ms), damit der Text nicht zu schnell durchrauscht:
  delay(100);
  
}
