import argparse
from subprocess import Popen

parser = argparse.ArgumentParser(description="remove a submodule")

parser.add_argument('submodule',type=str)

args = parser.parse_args()

if not args.submodule:
    exit()

print(f"removing submodule {args.submodule}")

try:
    Popen(f"git submodule deinit {args.submodule}").wait()
    Popen(f"git rm {args.submodule}").wait()
    Popen(f"git commit -am \"removed submodule {args.submodule}\"").wait()
    Popen(f"rm -rf .git/modules/{args.submodule}").wait()
    print("removal succeeded")

except:
    print("removal failed")
    Popen(f"git reset --hard")

    