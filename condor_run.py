import os
import sys
import time

# Make condor .jdl file
jdl_path = "./condor_run_{}.jdl".format(time.time())
os.system("cp ~/condor_template.jdl {}".format(jdl_path))
