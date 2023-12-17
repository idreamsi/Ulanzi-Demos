// Demo Programm fuer die Ulanzi TC-001 Anzeige: Animation 1

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
}

// Ein Schritt der Animation
void katze() {
  // Welches Einzelbild angezeigt werden soll.
  // "static" bedeutet, dass "einzelbild_nummer" einmalig mit 0 initialisiert wird,
  // danach wird diese Zeile uebersprungen
  static int einzelbild_nummer = 0;

  // Die 4 Einzelbilder, aus denen die Animation besteht.  Jedes Einzelbild
  // ist eine Grafik wie in Demo3
  // "Cat" from https://pixelit-project.github.io/PixelIt/webui/#/gallery
  uint16_t cat[4][64] {{33808,0,0,0,0,0,0,33808,43680,33808,0,0,0,0,33808,43680,43680,33808,44373,44373,44373,44373,33808,43680,33808,65535,65535,44373,44373,65535,65535,33808,33808,65535,0,44373,44373,65535,0,33808,33808,65535,0,33808,33808,65535,0,33808,0,33808,33808,43680,43680,33808,33808,0,0,0,33808,33808,33808,33808,0,0},
                       {33808,0,0,0,0,0,0,33808,43680,33808,0,0,0,0,33808,43680,43680,33808,44373,44373,44373,44373,33808,43680,33808,65535,65535,44373,44373,65535,65535,33808,33808,0,65535,44373,44373,0,65535,33808,33808,0,65535,33808,33808,0,65535,33808,0,33808,33808,43680,43680,33808,33808,0,0,0,33808,33808,33808,33808,0,0},
                       {33808,0,0,0,0,0,0,33808,43680,33808,0,0,0,0,33808,43680,43680,33808,44373,44373,44373,44373,33808,43680,33808,65535,65535,44373,44373,65535,65535,33808,33808,65535,0,44373,44373,65535,0,33808,33808,65535,0,33808,33808,65535,0,33808,0,33808,33808,43680,43680,33808,33808,0,0,0,33808,33808,33808,33808,0,0},
                       {33808,0,0,0,0,0,0,33808,43680,33808,0,0,0,0,33808,43680,43680,33808,44373,44373,44373,44373,33808,43680,33808,44373,44373,44373,44373,44373,44373,33808,33808,44373,44373,44373,44373,44373,44373,33808,33808,0,0,33808,33808,0,0,33808,0,33808,33808,43680,43680,33808,33808,0,0,0,33808,33808,33808,33808,0,0}};
  // Das aktuelle Einzelbild anzeigen.
  // Die x-Position soll so sein, dass die Animation in der Mitte der
  // Anzeige dargestellt wird. Die 8/2 sind die halbe Breite des Einzelbildes, das
  // 8 Pixel breit ist.
  matrix->drawRGBBitmap(MATRIX_BREITE / 2 - 8 / 2, 0, cat[einzelbild_nummer], 8, 8);

  // Anzeigen nicht vergessen, sonst bleibt's dunkel
  matrix->show();

  // Naechste Runde soll das naechste Einzelbild der Animation angezeigt werden
  einzelbild_nummer++;

  // Wenn wir hinter dem letzten Bild sind, springe wieder zum ersten Bild:
  if (einzelbild_nummer >= 4)
  {
    einzelbild_nummer = 0;
  }

  // Kurze Pause, damit die Animation nicht zu schnell ablaeuft:
  delay(350);
}

//--------------------------------------------------------------
void loop() {
  // In dieser Endlosschleife wird der Bildschirm geloescht und
  // dann das naechste Einzelbild der Animation ausgegeben.
  matrix->clear();
  katze();
}
