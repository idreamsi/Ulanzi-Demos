// Demo-Programm fuer die Ulanzi TC-001: Anzeige einer kleinen 8x8 Grafik

// Board Manager:  "ESP32" (von "Expressif Systems") hinzufuegen
//
// Library Manager: "FastLED NeoMatrix" (von Marc Merlin) hinzufuegen und alles,
//                  was dann vorgeschlagen wird
//
// Einstellungen:
// Board: ESP32 Dev Module
// Upload Speed: 230400
// CPU Frequency: 240 MHz (WiFi/BT)
// Flash Frequency: 80 MHz
// Flash Mode: QIO
// Flash Size: 4 MB (32Mb)
// Partition Scheme: Default 4 MB with spiffs (1.2 MB APP/1.5 MB SPIFFS)
// Core Debug Level: None
// PSRAM: Disabled
// Port: bei mir /dev/cu.usbserial-2210, kann bei Dir aber anders sein
// Wenn das Flashen fehlschlaegt, einfach oefters probieren. Wenn es gar nicht geht,
// hilft manchmal, die Anzeige aus- und wieder einzuschalten.

#include <Arduino.h>

// Funktions-Bibliotheken fuer die LED-Anzeige.
// Die eigentlichen Funktionen, die man selbst aufruft, sind aber in
// Adafruit_GFX, das von den beiden Bibliotheken eingebunden wird.
// Anleitung dazu: https://learn.adafruit.com/adafruit-gfx-graphics-library
// Alle Funktionen in der Uebersicht:
// https://github.com/adafruit/Adafruit-GFX-Library/blob/master/Adafruit_GFX.h
#include <FastLED_NeoMatrix.h>
#include <FastLED.h>

// An welchen Pin die LEDs angeschlossen sind:
#define MATRIX_PIN 32

// An Pin 15 ist ein Piepser, der zu leise ist und auch sonst nicht sehr
// nuetzlich ist.
#define PIEPSER_PIN 15

// Anzahl der LEDs in der Breite und Hoehe:
#define MATRIX_BREITE 32
#define MATRIX_HOEHE 8

// Die LED-Matrix als Objekt:
CRGB leds[MATRIX_BREITE * MATRIX_HOEHE];
FastLED_NeoMatrix *matrix;

// Der Text, der angezeigt werden soll
char* text = "Heute ist ein schoener Tag";


void setup() {
  // Piepser stumm schalten
  pinMode(PIEPSER_PIN, OUTPUT);
  digitalWrite(15, LOW);
  
  // LED Matrix initialisieren:
  FastLED.addLeds<NEOPIXEL, MATRIX_PIN>(leds, MATRIX_BREITE * MATRIX_HOEHE);
  matrix = new FastLED_NeoMatrix(leds, MATRIX_BREITE, MATRIX_HOEHE,
     NEO_MATRIX_TOP + NEO_MATRIX_LEFT + NEO_MATRIX_ROWS + NEO_MATRIX_ZIGZAG);
  matrix->begin();

  // Helligkeit geht von 0-255, wir nehmen einen mittleren Wert:
  matrix->setBrightness(155);

  // Anzeige loeschen:
  matrix->clear();
  
  // Zwei Grafiken anzeigen.
  // "Mario" und "Luigi" sind von https://pixelit-project.github.io/PixelIt/webui/#/gallery
  // Auf das "i" im Kreis klicken, um die Zahlen fuer die Grafik zu sehen
  // Man kann hier eigene Grafiken entwerfen und dann die Zahlen in unser Programm kopieren:
  // https://pixelit-project.github.io/PixelIt/webui/#/creator
  uint16_t icon1[64] {0,0,63650,63650,63650,63650,0,0,     // Pixelfarben fuer die 1. Zeile
                      0,0,63650,63650,63650,63488,63488,0, // 2. Zeile
                      0,0,65139,25388,65139,25388,0,0,     // 3. Zeile usw.
                      0,0,65139,65139,39296,39296,0,0,
                      65139,63488,12918,63488,63488,12918,63488,65139,
                      0,0,12918,12918,12918,12918,0,0,
                      0,0,12918,12918,12918,12918,0,0,
                      0,0,39296,0,0,39296,0,0};
  // Hier alle Zahlen in einer langen Zeile, das geht auch
  uint16_t icon2[64] {0,0,3745,3745,3745,3745,0,0,0,0,3745,3745,3745,3745,3745,0,0,0,65139,25388,65139,25388,0,0,0,0,65139,65139,39296,39296,0,0,65139,3745,12918,3745,3745,12918,3745,65139,0,0,12918,12918,12918,12918,0,0,0,0,12918,12918,12918,12918,0,0,0,0,39296,0,0,39296,0,0};
  
  // Erste Grafik bei (0,0) anzeigen, also ganz links.  
  // Die 8, 8 am Ende bedeutet, dass die Grafik 8x8 Pixel hat.
  matrix->drawRGBBitmap(0, 0, icon1, 8, 8);

  // Die zweite Grafik bei x=10, also mit 2 Pixeln Abstand zur ersten Grafik
  matrix->drawRGBBitmap(10, 0, icon2, 8, 8);

  // Anzeigen nicht vergessen!
  matrix->show();
}



//--------------------------------------------------------------
void loop() {
 // Nichts
}
