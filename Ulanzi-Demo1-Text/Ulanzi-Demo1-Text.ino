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

// There is a beeper on pin 15 that is too quiet and is otherwise not very useful.
#define PIEPSER_PIN 15

// Number of LEDs in width and height:
#define MATRIX_BREITE 32
#define MATRIX_HOEHE 8

// The LED matrix as an object:
CRGB leds[MATRIX_BREITE * MATRIX_HOEHE];
FastLED_NeoMatrix *matrix;


void setup() {
  // Mute beeper
  pinMode(PIEPSER_PIN, OUTPUT);
  digitalWrite(15, LOW);
  
  // Initialize LED matrix:
  FastLED.addLeds<NEOPIXEL, MATRIX_PIN>(leds, MATRIX_BREITE * MATRIX_HOEHE);
  matrix = new FastLED_NeoMatrix(leds, MATRIX_BREITE, MATRIX_HOEHE,
     NEO_MATRIX_TOP + NEO_MATRIX_LEFT + NEO_MATRIX_ROWS + NEO_MATRIX_ZIGZAG);
  matrix->begin();

  // Brightness goes from 0-255, we take a medium value:
  matrix->setBrightness(155);

  // Text-Farbe einstellen: Orange!
  // Hier kann man Farben auswaehlen und die Rot/Gruen/Blau-Werte ablesen:
  // https://www.rapidtables.org/de/web/color/RGB_Color.html
  matrix->setTextColor(matrix->Color(255, 128, 0));
  
  // Wenn der Text zu lang ist, nicht eine neue Zeile anfangen (die LED-Matrix
  // kann nur eine Zeile darstellen)
  matrix->setTextWrap(false);
  
  // Alles auf der Anzeige loeschen:
  matrix->clear();

  // Start-Position fuer den Text einstellen.
  // (0, 0) bedeutet (x=0, y=0), was oben links ist. (31, 7) ist die rechte
  // untere Ecke der Anzeige.
  // Wichtig: Wenn man eine andere Schriftart einstellt, muss man die Start-Position
  // auf (0,7) setzen, also unten links:  matrix->setCursor(0, 7);
  matrix->setCursor(0, 0);
  
  // Text ausgeben. Es passt nicht alles auf die Anzeige.
  matrix->print("Hallihallo");

  // Und noch eine Linie quer von oben links nach unten rechts darueber zeichnen.
  // Der Text wurde zuerst gedruckt, die Linie danach. Deshalb ist die Linie ueber
  // dem Text und verdeckt ihn.
  matrix->drawLine(0, 0, 31, 7, matrix->Color(80, 200, 80));
  
  // Alles anzeigen.  Wichtig: Wenn man das vergisst, wird nichts angezeigt.
  matrix->show();
  
}

void loop() {
  // Leer, die Anzeige soll ja nicht veraendert werden.
}
