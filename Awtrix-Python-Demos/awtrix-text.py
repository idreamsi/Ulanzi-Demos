#!/usr/bin/env python3

# Programm zum Anzeigen von Text auf der AWTRIX-LED-Matrix
# Wenn der Text laenger ist als die Matrix breit ist, dann wird er
# automatisch als Laufschrift angezeigt.
# Nach einer Weile verschwindet der Text wieder und die Uhrzeit wird
# wieder angezeigt.
#
# Beispiel: Anzeigen von "Hallo" in gelb (die Standardfarbe):
#           ./awtrix-text.py Hallo
# Beispiel: Anzeigen von "Heute ist ein schoener Tag" in hellblau.
#           Weil der Text aus mehreren Woertern besteht, muss er in
#           Anfuehrungszeichen gesetzt werden:
#           ./awtrix-text.py "Heute ist ein schoener Tag" 00ffff
#
# Siehe https://blueforcer.github.io/awtrix-light/#/api?id=custom-apps-and-notifications

import requests
import json
import argparse

# IP-Adresse der Ulanzi TC-001 bzw. der AWTRIX-LED-Matrix
adresse = "10.0.0.73"

# Kommandozeilenargumente einlesen
parser = argparse.ArgumentParser(description='AWTRIX Fernsteuerung: Text und Laufschrift')

# Welche Parameter sind moeglich?
parser.add_argument('text', type=str, help='Der anzuzeigende Text')
# Wenn nichts angegeben wird, wird die Farbe d2d200 (gelb) verwendet
parser.add_argument('farbe', type=str, default="d2d200", nargs='?',
                     help='Die Farbe als RGB Hexadezimalwert oder "aus". Wenn nichts angegeben wird, wird die Farbe d2d200 (gelb) verwendet')

args = parser.parse_args()

# Falls die Farbe "aus" ist, dann wird das durch die Farbe Schwarz (000000) erreicht
if args.farbe == "aus":
    args.farbe = "000000"

# Jetzt haben wir alle Daten fuer den HTTP-Request
url = f"http://{adresse}/api/notify"
data = {"text": f"{args.text}", "color": f"#{args.farbe}"}
# Dieser Header ist noetig, weil wir JSON-Daten senden
headers = {'Content-Type': 'application/json'}

# Und: Abschicken!
response = requests.post(url, data=json.dumps(data), headers=headers)

# Jetzt die Antwort ausgeben
print(response.status_code)
print(response.text)

