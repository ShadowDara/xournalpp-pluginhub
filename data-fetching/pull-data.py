import os
import sys
import json
from pathlib import Path
from dataclasses import dataclass
from typing import List, Optional
import requests


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
    link: str
    available_for: List[str]
    other_versions: Optional[List[OtherVersion]] = None


# *************************************************
# *                                               *
# *                   Variables                   *
# *                                               *
# *************************************************

plugindatafolder = "registration"
plugin_errors = []

script_path = os.path.dirname(__file__)
base_path = Path(__file__).parent.parent
json_path = os.path.join(base_path, plugindatafolder)

all_files = [os.path.join(json_path, f) for f in os.listdir(json_path)]

# List to store the all registration links in JSON format
regi_files = []

# List to store the plugin data in JSON format
plugin_data_list = []


# *************************************************
# *                                               *
# *                   Functions                   *
# *                                               *
# *************************************************

def from_dict(data: dict) -> IndexFile:
    other_versions_data = data.get("other_versions")
    other_versions = [OtherVersion(**v) for v in other_versions_data] if other_versions_data else None
    return IndexFile(
        name=data["name"],
        namespace=data["namespace"],
        author=data["author"],
        description=data["description"],
        license=data["license"],
        version=data["version"],
        link=data["link"],
        available_for=data["available_for"],
        other_versions=other_versions
    )

# *************************************************
# *                                               *
# *                Executing Code                 *
# *                                               *
# *************************************************

print("Starting to process registration files...\n")

"""
The Code will go through the file list in plugin registration,
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
    # Problem: The Links need to be formatted before

    """
    Future Problem:
    an exeption is needed here, if the does not lead to github
    """
    print(entry.main_link)
    formatted_link = entry.main_link.replace("github.com", "raw.githubusercontent.com").replace("tree/", "refs/heads/")
    print(formatted_link)

    response = requests.get(formatted_link + "/index.json")

    if response.status_code == 200:
        print("Link is available, processing...")
    
    # Error 1
    else:
        # Plugin is not available or the link is broken
        # so the programm will skip this plugin
        print(f"Skipping {entry.main_link}")
        plugin_errors.append(f"Plugin {entry.main_link} could not be accessed. / (1: Status code: {response.status_code})")
        continue

    try:
        json_data = json.loads(response.text)
        index_file = from_dict(json_data)
        
        # Now the json syntax of the index file is valid

        # Things which still needs to be checked:
        # - namespace must be unique
        # - character check for the namespace
        # - Most of the values are not allowed to be empty
        # - the Repository must although contain some code files for the plugin

    # Error 2
    except Exception as e:
        print(f"Skipping {entry.main_link}")
        plugin_errors.append(f"Plugin {entry.main_link} could not be accessed. / (2: Error code: {e})")
        continue

    # then append the data to the main json file
    plugin_data_list.append(json_data)

# Save the plugin data to a JSON file
with open(os.path.join(base_path, "data", "plugins.json"), "w", encoding="UTF-8") as f:
    json.dump(plugin_data_list, f, ensure_ascii=False, separators=(',', ':'))

# to end the program
# check for skipped plugins before exiting
if plugin_errors:
    print("\n******************************************************************\n")
    print("Some plugins were skipped:")
    for error in plugin_errors:
        print(f" - {error}")

    print("\n******************************************************************\n")
    print("Exit 1: Some plugins were skipped, please check the errors above.")
    sys.exit(1)

# If everything went fine, exit with code 0
print("\n******************************************************************\n")
print("Exit 0: All plugins were processed successfully.")
sys.exit(0)
