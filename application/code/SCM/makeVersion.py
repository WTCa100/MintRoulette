import subprocess
import os
from pathlib import Path
import sys

def get_config_version(path):
    with open(path, "r") as config_lines:
        lines = config_lines.readlines()
        for i, line in enumerate(lines):
            if line.startswith("gameVersion    :"):
                versionNumber = line[line.find(':')+1:]
                break
    return versionNumber
                
def build_new_version(oldVersion, pathWeight):
    major, minor, patch = [int(x) for x in oldVersion.split(".")]
    if pathWeight == "major":
        major += 1
        minor = 0
        patch = 0
    elif pathWeight == "minor":
        minor += 1
        patch = 0
    elif pathWeight == "patch":
        patch += 1
    else:
        print(f"Could not change current version:{oldVersion}With:{pathWeight}Reason: Tag not recognized")
        print("Keeping old version in tact.")
        return oldVersion

    return f"{major}.{minor}.{patch}"

def update_version(version, path):
    #update init.cfg
    with open(path, "r") as f:
        lines = f.readlines()
    for i, line in enumerate(lines):
        if line.startswith("gameVersion    :"):
            lines[i] = f"gameVersion    :{version}\n"
    with open(path, "w") as f:
        f.writelines(lines)
    #update version.txt
    with open("./version.game", "w") as helper:
        helper.writelines(f"gameVersion:{version}")
        
if __name__ == "__main__":
    # check for errors
    print(sys.argv[2])
    if not len(sys.argv) == 3:
        print("There must be an argument specifying update weight and init.cfg path! Game version will remain the same.")
        print("Usage: py makeVersion.py [init.cfg path] [patchWeight]")
        quit(1)
    
    extractedPath = Path(sys.argv[1])
    if not extractedPath.is_file():
        print(f"No such file in directory {extractedPath}. Game version will remain the same.")
        quit(1)
    
    extractedPatchWeight = sys.argv[2].lower()
    if not(extractedPatchWeight == "major" or extractedPatchWeight == "minor" or extractedPatchWeight == "patch"):
        print("Forbidden argument. Allowed argunments are: \"major\" , \"minor\" and \"patch\". Game version will remain the same.")
        quit(1)

    oldVersion = get_config_version(extractedPath)
    version = build_new_version(get_config_version(extractedPath), extractedPatchWeight)
    if oldVersion == version:
        print("Old version is the same as new version, no changes applied")
        quit(1)
    else:
        print(f"Swapped game from {oldVersion} to {version}")
        update_version(version, extractedPath)
        quit(0)
        