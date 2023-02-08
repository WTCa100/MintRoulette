import subprocess
import os
import sys

def get_config_version():
    with open("./bin/init.cfg", "r") as config_lines:
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

def update_version(version):
    with open("./bin/init.cfg", "r") as f:
        lines = f.readlines()
    for i, line in enumerate(lines):
        if line.startswith("gameVersion    :"):
            lines[i] = f"gameVersion    :{version}\n"
    with open("./bin/init.cfg", "w") as f:
        f.writelines(lines)
        
if __name__ == "__main__":
    print(len(sys.argv))
    version = build_new_version(get_config_version(), sys.argv[1]) 
    print(version)
    #update_version(version)