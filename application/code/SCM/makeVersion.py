import subprocess
import os
from pathlib import Path
import sys

relativeGitHookConfigPath = "../../application/bin/init.cfg"

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
    elif pathWeight == "minor":
        minor += 1
    elif pathWeight == "patch":
        patch += 1
    else:
        print(f"Could not change current version:{oldVersion}With:{pathWeight}Reason: Tag not recognized")
        print("Keeping old version in tact.")
        return oldVersion

    return f"{major}.{minor}.{patch}"

def update_version(version, path):
    with open(path, "r") as f:
        lines = f.readlines()
    for i, line in enumerate(lines):
        if line.startswith("gameVersion    :"):
            lines[i] = f"gameVersion    :{version}\n"
    with open(relativeGitHookConfigPath, "w") as f:
        f.writelines(lines)
        
if __name__ == "__main__":
    
    # check for errors
    print(len(sys.argv))
    if not len(sys.argv) == 3:
        print("There must be an argument specifying update weight and init.cfg path! Game version will remain the same.")
        print("Usage: py makeVersion.py [init.cfg path] [patchWeight]")
        quit()
    
    extractedPath = Path(sys.argv[1])
    if not extractedPath.is_file():
        print(f"No such file in directory {extractedPath}. Game version will remain the same.")
        quit()
    
    extractedPatchWeight = sys.argv[2].lower()
    if not(extractedPatchWeight == "major" or extractedPatchWeight == "minor" or extractedPatchWeight == "patch"):
        print("Forbidden argument. Allowed argunments are: \"major\" , \"minor\" and \"patch\". Game version will remain the same.")
        quit()

    oldVersion = get_config_version(extractedPath)
    version = build_new_version(get_config_version(extractedPath), extractedPatchWeight)
    if oldVersion == version:
        quit()
    else:
        print(version)
        update_version(version, extractedPath)
        