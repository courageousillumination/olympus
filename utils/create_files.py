#! /usr/bin/python
import sys
import os

USAGE = "Usage: create_files.py [FILE_PREFIX]"

if __name__ == "__main__":
    if len(sys.argv) != 2:
        print(USAGE)
        sys.exit(-1)
        
    full_path = sys.argv[1]
    directory, file_name = os.path.split(full_path)
    
    src_path = os.path.join("../src", directory)
    inc_path = os.path.join("../inc", directory)
    test_path = os.path.join("../test", directory)
    
    if not os.path.exists(src_path):
        os.makedirs(src_path)
    if not os.path.exists(inc_path):
        os.makedirs(inc_path)
    if not os.path.exists(test_path):
        os.makedirs(test_path)
        
        
    #Create the directory if necessary
    src = open(os.path.join(src_path, file_name + ".cpp"), "w")
    src.write('#include "{0}"\n'.format(full_path + ".hpp"))
    src.close()
    
    #Create the test file
    test = open(os.path.join(test_path, file_name + "_test.cpp"), "w")
    #test.write('#include <gtest/gtest.h>\n\n#include "{0}"\n'.format(full_path + ".hpp"))
    test.write('#include <gtest/gtest.h>\n\n#include "olympus.hpp"\n')
    test.close()
    
    inc = open(os.path.join(inc_path, file_name + ".hpp"), "w")
    full_path = full_path.replace('/', '__')
    full_path = full_path.upper()
    macro = "OLYMPUS__"+full_path
    inc.write('#ifndef {0}\n'.format(macro))
    inc.write('#define {0}\n'.format(macro))
    inc.write('#endif\n')
    inc.close()
    
