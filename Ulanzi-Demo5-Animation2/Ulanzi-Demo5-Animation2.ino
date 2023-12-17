// Demo Programm fuer die Ulanzi TC-001 Anzeige: Animation 2

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

// Andere Schriftart von PixelIt, die schmaler ist und dadurch weniger
// Platz braucht:
// https://github.com/aptonline/PixelIt_Ulanzi/blob/main/src/PixelIt.ino
#include "PixelItFont.h"

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

// Anzahl der Einzelbilder in der Animation
#define ANZ_BILDER 8


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

  // Wenn der Text zu lang ist, nicht eine neue Zeile anfangen (die LED-Matrix
  // kann nur eine Zeile darstellen)
  matrix->setTextWrap(false);
  
  // Textfarbe einstellen.
  // Hier kann man Farben auswaehlen und die Rot/Gruen/Blau-Werte ablesen:
  // https://www.rapidtables.org/de/web/color/RGB_Color.html
  matrix->setTextColor(matrix->Color(255, 128, 0));
  
  // Die schmale Schrift auswaehlen
  matrix->setFont(&PixelItFont);
  
  // Anzeige loeschen:
  matrix->clear();
}


// Ein Schritt der Animation
void wandersmann() {
  static int einzelbild_nummer = 0;
  
  // Der Wandersmann soll von links in's Bild kommen
  static int x_position = -8;
  // "Hiker" from https://pixelit-project.github.io/PixelIt/webui/#/gallery
  uint16_t mann[ANZ_BILDER][64] {{0,0,35491,35491,65371,0,0,0,0,0,0,65371,65371,65371,0,0,0,0,0,65371,31,0,0,0,0,0,0,65371,31,0,0,0,0,0,0,65371,31,0,0,0,0,0,0,31,31,0,0,0,0,0,65371,31,31,0,0,0,0,0,0,65371,65371,0,0,0},
                        {0,0,35491,35491,65371,0,0,0,0,0,0,65371,65371,65371,0,0,0,0,0,65371,31,0,0,0,0,0,65371,31,31,0,0,0,0,0,65371,31,31,0,65371,0,0,0,0,31,31,0,65371,0,0,0,31,31,0,65371,0,0,0,0,65371,65371,0,0,0,0},
                        {0,0,35491,35491,35491,0,0,0,0,0,0,35491,65371,0,0,0,0,0,0,65371,65371,65371,0,0,0,0,65371,65371,31,0,0,0,0,0,65371,31,31,0,0,0,0,65371,65371,31,31,31,0,0,0,0,31,31,31,31,0,0,0,65371,65371,0,0,65371,65371,0},
                        {0,0,35491,35491,65371,35491,0,0,0,0,35491,65371,65371,65371,0,0,0,0,0,65371,31,0,0,0,0,0,0,65371,31,0,0,0,0,0,65371,31,31,0,0,0,0,0,0,31,31,0,0,0,0,65371,31,31,31,31,0,0,0,65371,0,0,65371,65371,0,0},
                        {0,0,35491,35491,65371,0,0,0,0,0,35491,65371,65371,65371,0,0,0,0,0,65371,31,0,0,0,0,0,0,31,65371,0,0,0,0,0,0,65371,31,0,0,0,0,0,0,31,31,0,0,0,0,0,65371,31,31,0,0,0,0,0,0,65371,65371,0,0,0},
                        {0,0,35491,35491,65371,0,0,0,0,0,0,65371,65371,65371,0,0,0,0,0,65371,31,0,0,0,0,0,0,31,65371,0,0,0,0,0,0,31,65371,0,65371,0,0,0,0,31,31,0,65371,0,0,0,31,31,0,65371,0,0,0,0,65371,65371,0,0,0,0},
                        {0,0,35491,35491,35491,0,0,0,0,0,0,35491,65371,0,0,0,0,0,0,65371,65371,65371,0,0,0,0,0,31,65371,0,0,0,0,0,0,31,65371,0,0,0,0,0,0,31,31,65371,0,0,0,0,31,31,31,31,0,0,0,65371,65371,0,0,65371,65371,0},
                        {0,0,35491,35491,65371,35491,0,0,0,0,35491,65371,65371,65371,0,0,0,0,0,65371,31,0,0,0,0,0,0,65371,31,0,0,0,0,0,0,31,65371,0,0,0,0,0,0,31,31,0,0,0,0,65371,31,31,31,31,0,0,0,65371,0,0,65371,65371,0,0}};
  // Aktuelles Einzelbild der Animation anzeigen:
  matrix->drawRGBBitmap(x_position, 0, mann[einzelbild_nummer], 8, 8);
  
  // Das Maennchen zieht einen Text hinter sich her. Der Text faengt 15 Pixel hinter
  // dem Maennchen an
  matrix->setCursor(x_position - 15, MATRIX_HOEHE);
  matrix->print("HURZ");

  // Alles anzeigen:
  matrix->show();

  // Zum naechsten Einzelbild gehen:
  einzelbild_nummer++;
  
  // Und ein Pixel nach vorne gehen (Maennchen und Text)
  x_position++;

  // Zum Anfang, wenn das Ende der Animation erreicht ist:
  if (einzelbild_nummer >= ANZ_BILDER)
  {
    einzelbild_nummer = 0;
  }

  // Wenn auch der Text aus dem Bild rausgewandert ist, wieder von links anfangen:
  if (x_position > 50)
  {
    x_position = -8;
  }  

  // Etwas warten, sonst laeuft der Wandersmann zu schnell
  delay(200);
}

//--------------------------------------------------------------
void loop() {
  matrix->clear();
  wandersmann();
}
