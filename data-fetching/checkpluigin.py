import os
import sys
import json
from pathlib import Path
from dataclasses import dataclass
from typing import List, Optional
import requests

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

def check_subversion(entry):
    # other versions durchgehen
    return None

# Input Argument is the file path of the file located in
# registration/*.json
def check_pluigin(file):
    # open the file and check the content
    with open(file, "r", encoding="UTF-8") as f:
        content = f.read()
        data = json.loads(content)

        # Return when the file is empty
        if data is None:
            # Error 4
            return "Plugin could not be accessed! Registration file is empty. (4))", None

        entry = registration_file(**data)

    # The Code will open the link
    # and copy the index file on Github and
    # check if the file is working
    print(entry.main_link)
    formatted_link = entry.main_link.replace("github.com", "raw.githubusercontent.com").replace("tree/", "refs/heads/")
    print(formatted_link)

    response = requests.get(formatted_link + "/index.json")

    if response.status_code == 200:
        print("Link is available, processing...")
    
    else:
        # Plugin is not available or the link is broken
        # so the programm will skip this plugin
        print(f"Skipping {entry.main_link}")
        # Error 1
        return f"Plugin {entry.main_link} could not be accessed. / (1: Status code: {response.status_code})", None

    try:
        plugin_data = json.loads(response.text)
        index_file = from_dict(plugin_data)

        # Now the json syntax of the index file is valid

        filename = Path(file).stem

        # namespace must be the same as the name of the registration file
        if index_file.namespace != filename:
            # Error 3
            return f"Plugin {entry.main_link} has no unique Namespace. / (3: Error code: no unique namespace!)", None
        
        if index_file.other_versions is not None:
            for ventry in index_file.other_versions:
                error = check_subversion(ventry)
                if error is not None:
                    return error

        # Things which still needs to be checked:

        # - the Repository must although contain some code files for the plugin
        # - sub versions of the plugin still need to be checked (easy because of branches now!)

    # Error 2
    except Exception as e:
        print(f"Skipping {entry.main_link}")
        return f"Plugin {entry.main_link} could not be accessed. / (2: Error code: {e})", None

    # then append the data to the main json file
    # plugin_data_list.append(json_data)

    return None, plugin_data

if __name__ == "__main__":
    pass
