import os
import sys
import json
from pathlib import Path
from dataclasses import dataclass
from typing import List, Optional
import requests

import checkpluigin

def main():
    pass

if __name__ == "__main__":
    print("\n******************************************************************\n")
    print(" Checking Plugins")
    print("\n******************************************************************\n")
    
    plugindatafolder = "registration"
    
    script_path = os.path.dirname(__file__)
    base_path = Path(__file__).parent.parent
    json_path = os.path.join(base_path, plugindatafolder)

    # List for all Registration Files
    all_files = [os.path.join(json_path, f) for f in os.listdir(json_path)]

    # List to store the plugin data in JSON format
    plugin_data_list = []
    plugin_error_list = []

    for file in all_files:
        error, data = checkpluigin.check_pluigin(file)
        if data is not None:
            plugin_data_list.append(data)
        if error is not None:
            plugin_error_list.append(error)

    # At the End:
    # Write plugin data in a JSON File and print errors in the console
    # (or a log file idk)
    
    # Save the plugin data to a JSON file
    with open(os.path.join(base_path, "data", "plugins.json"), "w", encoding="UTF-8") as f:
        json.dump(plugin_data_list, f, ensure_ascii=False, separators=(',', ':'))
    
    # check for skipped plugins before exiting
    if plugin_error_list:
        print("\n******************************************************************\n")
        print("Some plugins were skipped:")
        for error in plugin_error_list:
            print(f" - {error}")

        print("\n******************************************************************\n")
        print("Exit 1: Some plugins were skipped, please check the errors above.")
        sys.exit(1)

    # If everything went fine, exit with code 0
    print("\n******************************************************************\n")
    print("Exit 0: All plugins were processed successfully.")
    sys.exit(0)
