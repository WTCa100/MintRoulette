import subprocess


if __name__ == "__main__":
    print("In order to update software version you must provide the following arguments:")
    versionWeight = input("Version weight (major, minor, patch):")

    if not (versionWeight.lower() == "major" or versionWeight.lower() == "minor" or versionWeight.lower() == "patch"):
        print("Those are forbidden arguments. Allowed arguments are \"major\", \"minor\" and \"patch\"")
        quit(1)
    
    initConfigPath = input("Init config path: (Optional)")
    
    if(len(initConfigPath) == 0):
        initConfigPath = "./application/bin/init.cfg"
    
    runProcess = subprocess.run(["python", "./application/code/SCM/makeVersion.py", initConfigPath, versionWeight], stdin=subprocess.PIPE, stdout=subprocess.PIPE, stderr=subprocess.PIPE)
    print(runProcess.stdout.decode())
    