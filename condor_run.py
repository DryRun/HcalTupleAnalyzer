import os
import sys
import time
sys.path.append(os.path.expandvars("$CMSSW_BASE/src/MyTools/RootUtils/python"))
import CondorJDLFile
from CondorJDLFile import CondorJDLFile
from subprocess import call
from sys import argv

if not len(argv)==5:
	print "Simple Usage:\n python run.py macros/analysisClass_HFPhaseScan.C config/input_lists/simple_list.txt config/tree_lists/treelist.txt output.root"
	print "2-input type Usage:\n python run.py macros/analysisClass_uHBHECommissioning.C config/input_lists/main_input.txt config/tree_lists/tree_list.txt output.root"
	exit(1)
else:
	# Normal run.py 
	if(os.path.exists("./src/analysisClass.C")):
		if not argv[1] in  os.readlink("./src/analysisClass.C") and os.path.exists("./src/analysisClass.o"):
			os.remove("./src/analysisClass.o")
		os.remove("./src/analysisClass.C")
	os.symlink("../%s"%argv[1],"./src/analysisClass.C")
	exitcode = call("make")
	if not exitcode==0:
		print "Compile failed ... "
	else:
		# Make a submit directory and change to it
		hcalTupleAnalyzer_dir = os.getcwd()
		ts = int(round(time.time()))
		submit_dir = "condor_submit/submit_{}".format(ts)
		os.system("mkdir -pv {}".format(submit_dir))
		os.chdir(submit_dir)
		
		# Make condor .jdl file
		jdl = CondorJDLFile(".")
		jdl.set_executable("{}/main".format(hcalTupleAnalyzer_dir))

		job_name = argv[1].replace("macros/analysisClass_", "").replace(".C", "")
		print "Setting job name = {}".format(job_name)
		jdl.set_job_name(job_name)

		# Input files
		input_files_to_copy = []

		# Make separate input.txt files for each input ROOT file. Register both the input.txt and the ROOT file in the .jdl inputs-to-copy
		n_input_ROOT_files = 0
		input_ROOT_files_txt = open(hcalTupleAnalyzer_dir + "/" + argv[2], 'r')
		new_input_txt_basepath = "condor_input_list_$(Process).txt"
		for line in input_ROOT_files_txt:
			line = line.rstrip()
			if len(line) > 0:
				input_files_to_copy.append(line)
				new_input_txt_path = new_input_txt_basepath.replace("$(Process)", "{}".format(n_input_ROOT_files))
				new_input_txt = open(new_input_txt_path, 'w')
				new_input_txt.write(os.path.basename(line) + "\n") # Basename the ROOT file path, because it will be copied to the condor scratch dir
				new_input_txt.close()
				input_files_to_copy.append(new_input_txt_path)
				n_input_ROOT_files += 1

		jdl.set_queue(str(n_input_ROOT_files))

		# Tree names file
		os.system("cp {}/{} tree_names.txt".format(hcalTupleAnalyzer_dir, argv[3]))
		input_files_to_copy.append("tree_names.txt")
		jdl.set_input_files(input_files_to_copy)

		# Pass the arguments to the .jdl file (i.e. arguments to ./main)
		arguments_string = os.path.basename(new_input_txt_basepath) + " tree_names.txt " + argv[4] + ".$(PROCESS)"
		jdl.add_arguments(arguments_string)

		# Submit
		jdl.submit()