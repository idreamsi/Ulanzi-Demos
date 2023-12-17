// Demo-Programm, das einen Text und eine Linie auf der Ulanzi TC-001 anzeigt

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
