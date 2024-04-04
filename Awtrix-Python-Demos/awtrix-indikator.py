#!/usr/bin/env python3

# Program for setting the indicators of the AWTrix LED matrix
# Example: Setting the upper indicator (number 1) on red:
# ./awtrix-indicator.py 1 ff0000
# Example: Switching off the upper indicator:
# ./awtrix-indikator.py 1 aus
# See https://blueforcer.github.io/awtrix-light/#/api?id=colored-indicators

import requests
import json
import argparse

# Read command line arguments
parser = argparse.ArgumentParser(description='AWTRIX Fernsteuerung: Indikatoren')

# Which parameters are possible?
parser.add_argument('indikator', type=int, help='Die Nummer des Indikators (1-3')
parser.add_argument('farbe', type=str, help='Die Farbe als RGB Hexadezimalwert oder "aus"')

args = parser.parse_args()

# If the color is "off", this is achieved by the color black (000000)
if args.farbe == "aus":
    args.farbe = "000000"

# Now we have all the data for the http request
url = f"http://10.0.0.73/api/indicator{args.indikator}"
data = {"color": f"#{args.farbe}"}
# This header is set up because we send JSON data
headers = {'Content-Type': 'application/json'}

# And: Submit!
response = requests.post(url, data=json.dumps(data), headers=headers)

# Now output the answer
print(response.status_code)
print(response.text)

