#!/usr/bin/env python
# -*- coding:utf-8 -*-

import re
import sys

if len(sys.argv) != 4:
	print 'usage: python remove_hd_suffix.py <file_path> <striga> <stringb>'
	exit()

file_path = sys.argv[1]
source = sys.argv[2]
destination = sys.argv[3]
file_handle = open(file_path, 'r')
file_content = file_handle.read()
file_handle.close()
file_handle = open(file_path, 'w')
file_handle.write(re.sub(source, destination, file_content))
file_handle.close()