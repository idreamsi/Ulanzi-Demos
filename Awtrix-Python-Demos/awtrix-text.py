#!/usr/bin/env python3

# Program for displaying text on the awtrix LED matrix
# If the text is Laenger than the matrix is wide, then it becomes
# automatically displayed as a head.
# After a while the text disappears and the time becomes
# again displayed.
#
# Example: Show "Hello" in yellow (the standard color):
#         ./awtrix-text.py Hello
# Example: Show "Today is a Schoener Tag" in light blue.
# Because the text consists of several Woertern, it must be in
# Desorting signs are set:
#         ./awtrix-text.py "Today is a beautiful day" 00ffff
#
# See https://blueforcer.github.io/awtrix-light/#/api?id=cUtom-apps-and-notifications

import requests
import json
import argparse

# IP address of the Ulanzi TC-001 or the AWTrix LED matrix
adresse = "10.0.0.73"

# Read command line arguments
parser = argparse.ArgumentParser(description='AWTRIX Fernsteuerung: Text und Laufschrift')

# Which parameters are possible?
parser.add_argument('text', type=str, help='Der anzuzeigende Text')
# If nothing is specified, the color D2D200 (yellow) is used
parser.add_argument('farbe', type=str, default="d2d200", nargs='?',
                     help='Die Farbe als RGB Hexadezimalwert oder "aus". Wenn nichts angegeben wird, wird die Farbe d2d200 (gelb) verwendet')

args = parser.parse_args()

# If the color is "off", this is achieved by the color black (000000)
if args.farbe == "aus":
    args.farbe = "000000"

# Now we have all the data for the http request
url = f"http://{adresse}/api/notify"
data = {"text": f"{args.text}", "color": f"#{args.farbe}"}
# This header is set up because we send JSON data
headers = {'Content-Type': 'application/json'}

# And: Submit!
response = requests.post(url, data=json.dumps(data), headers=headers)

# Now output the answer
print(response.status_code)
print(response.text)

