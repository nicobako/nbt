import argparse
import subprocess
from pathlib import Path

parser = argparse.ArgumentParser(description="run amcs samples")

parser.add_argument(
  "samples",
  help="the directory you would like to build",
  nargs="*",
  default=[d for d in Path('.').iterdir() if d.name != ".svn" and d.is_dir()]
)

args = parser.parse_args()

print(args.samples)


for sample in args.samples:
  subprocess.check_call(
    "g++ -o {0}-app -Wall -pthread -I../include/ ../src/**/*.cpp {0}/main.cpp -lrt".format(sample),
    shell=True
  )

  subprocess.run(["valgrind", "--leak-check=full", "--show-leak-kinds=all", "./{}-app".format(sample)])

  subprocess.run(["rm", "./{}-app".format(sample)])


