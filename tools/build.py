import subprocess, os

cmd = "premake\premake5.exe gmake"

subprocess.call(["powershell", "-Command", cmd])
subprocess.call(["powershell", "-Command", "make"])
