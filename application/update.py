import subprocess
from pathlib import Path


if __name__ == "__main__":
    print("In order to update software version you must provide the following arguments:")
    version_weight = input("Version weight (major, minor, patch):")

    if not (version_weight.lower() == "major" or version_weight.lower() == "minor" or version_weight.lower() == "patch"):
        print("Those are forbidden arguments. Allowed arguments are \"major\", \"minor\" and \"patch\"")
        quit(1)
    
    init_config_path = input("Init config path: (Optional)")
    
    if(len(init_config_path) == 0):
        init_config_path = list(Path('.').rglob('*init.cfg'))
    
    if len(init_config_path) > 1:
        print("More than one game config has been found! Please ensure that there is only one game config file present!")
        quit(1)
    
    init_config_path = init_config_path[0].absolute()
    
    # Find makeVersion
    make_version_path = list(Path('.').rglob('*makeVersion.py'))
    if len(make_version_path) > 1:
        print("More than one candidate match! Please make that there is only one makeVersion instance present!")
        quit(1)
    
    runProcess = subprocess.run(["python", str(make_version_path[0].absolute()), init_config_path, version_weight], stdin=subprocess.PIPE, stdout=subprocess.PIPE, stderr=subprocess.PIPE)
    print(runProcess.stdout.decode())
    print(runProcess.stderr.decode())