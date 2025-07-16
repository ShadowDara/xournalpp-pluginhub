import os
import sys
import json
from pathlib import Path
from dataclasses import dataclass
from typing import List, Optional


# *************************************************
# *                                               *
# *                   Ideas                       *
# *                                               *
# *************************************************

# 1. datein im ordner finden
# 2. jede datei öffnen
# 3. link aus jeder datei öffnen
# 4. index datei auslesen und sublinks abarbeiten
# 5. das alles in ein json file speichern

# safe datei: plugins.json


# *************************************************
# *                                               *
# *                 json data                     *
# *                                               *
# *************************************************

# Dataclass for the registration file
@dataclass
class registration_file:
    main_link: str

# Dataclasses for the Indexfile structure
@dataclass
class OtherVersion:
    version: str
    available_for: List[str]
    link: str

@dataclass
class IndexFile:
    name: str
    namespace: str
    author: str
    description: str
    license: str
    version: str
    available_for: List[str]
    other_versions: Optional[List[OtherVersion]] = None


# *************************************************
# *                                               *
# *                   Variables                   *
# *                                               *
# *************************************************

plugindatasafefile = "plugins.json"
plugindatafolder = "plugin-registration"
plugin_errors = []

script_path = os.path.dirname(__file__)
base_path = Path(__file__).parent.parent
json_path = os.path.join(base_path, plugindatafolder)

all_files = [os.path.join(json_path, f) for f in os.listdir(json_path)]

regi_files = []


# *************************************************
# *                                               *
# *                Executing Code                 *
# *                                               *
# *************************************************

"""
The Code will go through the file list in pluigin registration,
check if the json syntax is valid.
If so, the code will copy the main link and add it to a list of
Links
"""
for file in all_files:
    with open(file, "r", encoding="UTF-8") as f:
        content = f.read()
        data = json.loads(content)

        if data == None:
            continue

        data2 = registration_file(**data)
        regi_files.append(data2)


"""
The Code will open the link for every entry in regi_files
and copy the index file on Github, then look for their
sub files and althouth copy them!
"""
for entry in regi_files:
    print(entry.main_link)


# to end the program
# check for skipped plugins before exiting
if plugin_errors != []:
    print("Some plugins were skipped:")
    for error in plugin_errors:
        print(f" - {error}")
    sys.exit(1)

# If everything went fine, exit with code 0
sys.exit(0)
