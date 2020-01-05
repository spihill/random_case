#!/usr/bin/python3

import glob
import json
import codecs
import sys

def prefix_name(s):
	start = s.rfind('/') + 1
	end = s.rfind('.')
	return s[start:end]

def include_source(s):
	start = max(s.rfind('/'), s.find('"')) + 1
	end = s.rfind('"')
	return s[start:end]

def include_dir(s):
	start = s.find('"') + 1
	end = max(s.rfind('/'), s.find('"')) + 1
	return s[start:end]

def source_dir(s):
	if s.rfind('/') != -1:
		return s[0:s.rfind('/')+1]
	return ""

def source_file(s):
	if s.rfind('/') != -1:
		return s[s.rfind('/')+1:]
	return s

def source_load(name, read_flag):
	try:
		if read_flag == True:
			src = codecs.open(name, 'r', 'utf-8')
		else:
			src = codecs.open(name, 'w', 'utf-8')
		return src
	except Exception as e:
		print(e)
		src.close()
		exit(1)

def make_cpp_list(dir, source, result):
	src = source_load(dir + source, True)
	prefix = prefix_name(source)
	result['prefix'] = prefix
	result['body'] = []
	for idx, line in enumerate(src):
		if '#include' in line and '"' in line:
			indent = line[:line.find('#')]
			res = {}
			make_cpp_list(dir + include_dir(line), include_source(line), res)
			for r in res['body']:
				result['body'].append(indent + r)
		elif line[-1] == '\n':
			result['body'].append(line[:-1])
		else:
			result['body'].append(line)
	src.close()

def make_cpp_list_wrap(source, result):
	make_cpp_list(source_dir(source), source_file(source), result)