import os
import sys
import json

pluigindatafolder = "pluigin-registration"

# 1. datein im ordner finden
# 2. jede datei öffnen
# 3. link aus jeder datei öffnen
# 4. index datei auslesen und sublinks abarbeiten
# 5. das alles in ein json file speichern

# safe datei: pluigins.json

pluigindatasafefile = "pluigins.json"

print("Collecting Pluigin Data!")
