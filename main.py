import os
import sys


compileFlag = '-build' in sys.argv
if compileFlag:
    sys.argv.remove('-build')

version = sys.argv[1]

os.system(f'ln -snf {version.upper()} test')
os.chdir('test')
if compileFlag:
    os.system(f'qrun -br {" ".join(sys.argv[2:])}')
else:
    os.system(f'qrun {" ".join(sys.argv[2:])}')
