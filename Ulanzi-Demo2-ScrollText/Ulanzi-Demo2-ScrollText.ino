// Demo-Programm fuer die Ulanzi TC001, das eine Laufschrift anzeigt

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

  // Textfarbe einstellen.
  // Hier kann man Farben auswaehlen und die Rot/Gruen/Blau-Werte ablesen:
  // https://www.rapidtables.org/de/web/color/RGB_Color.html
  matrix->setTextColor(matrix->Color(255, 128, 0));

  // Wenn der Text zu lang ist, nicht eine neue Zeile anfangen (die LED-Matrix
  // kann nur eine Zeile darstellen)
  matrix->setTextWrap(false);

  // Die schmale Schrift auswaehlen
  matrix->setFont(&PixelItFont);
  
  // Alles auf der Anzeige loeschen:
  matrix->clear();
  
  // Start-Position fuer den Text einstellen.
  // Wichtig: Da wir eine andere Schriftart nutzen, muss die Start-Position
  // auf (0,7) gesetzt werden, also unten links:
  matrix->setCursor(0, 7);
  
  // Text ausgeben:
  matrix->print(text);

  // Alles anzeigen.  Wichtig: Wenn man das vergisst, wird nichts angezeigt.
  matrix->show();

  // Eine Sekunde warten, danach startet die Laufschrift
  delay(1000);

  // Andere Textfarbe fuer die Laufschrift, um es interessanter zu machen:
  matrix->setTextColor(matrix->Color(51, 255, 153));

}

// Berechne, wie viele Pixel der uebergebene Text breit ist.
// Die Funktion ist nicht ganz genau, es scheint, als ob immer ein paar
// Pixel mehr zurueckgegeben werden als der Text breit ist. Macht aber nix.
uint16_t textBreite(char* text)
{
  // Die Funktion "getTextBounds()" erwartet ein paar Variablen, die sie fuellt
  // (deshalb werden die Adressen der Variablen uebergeben, sonst
  // Wir haben nur interesse an der Breite
  int16_t ulx, uly;
  uint16_t breite, hoehe;
  matrix->getTextBounds(text, 0, 7, &ulx, &uly, &breite, &hoehe);
  return breite;
}


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
