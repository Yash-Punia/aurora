import os, sys;
import subprocess;

TOOLS_DIR = "tools"

def RunCommand(cmd):
    subprocess.call(["python3", "{}/{}/{}".format(os.getcwd(), TOOLS_DIR, cmd)])

for i in range(1,len(sys.argv)):
    cmd = sys.argv[i]
    RunCommand(cmd);
