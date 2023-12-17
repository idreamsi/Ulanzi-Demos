#!/usr/bin/env python3

# Programm zum Setzen der Indikatoren der AWTRIX-LED-Matrix
# Beispiel: Setzen des oberen Indikators (Nummer 1) auf rot:
#           ./awtrix-indikator.py 1 ff0000
# Beispiel: Ausschalten des oberen Indikators:
#           ./awtrix-indikator.py 1 aus
# Siehe https://blueforcer.github.io/awtrix-light/#/api?id=colored-indicators

import requests
import json
import argparse

# Kommandozeilenargumente einlesen
parser = argparse.ArgumentParser(description='AWTRIX Fernsteuerung: Indikatoren')

# Welche Parameter sind moeglich?
parser.add_argument('indikator', type=int, help='Die Nummer des Indikators (1-3')
parser.add_argument('farbe', type=str, help='Die Farbe als RGB Hexadezimalwert oder "aus"')

args = parser.parse_args()

# Falls die Farbe "aus" ist, dann wird das durch die Farbe Schwarz (000000) erreicht
if args.farbe == "aus":
    args.farbe = "000000"

# Jetzt haben wir alle Daten fuer den HTTP-Request
url = f"http://10.0.0.73/api/indicator{args.indikator}"
data = {"color": f"#{args.farbe}"}
# Dieser Header ist noetig, weil wir JSON-Daten senden
headers = {'Content-Type': 'application/json'}

# Und: Abschicken!
response = requests.post(url, data=json.dumps(data), headers=headers)

# Jetzt die Antwort ausgeben
print(response.status_code)
print(response.text)

