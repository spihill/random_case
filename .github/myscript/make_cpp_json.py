#!/usr/bin/python3

import glob
import json
import codecs
import resolve_includes

def file_list():
	ng_words = ['verify/', '.test.cpp','test/','develop/', 'for_include/']
	result = []
	files = glob.glob("../../**/*.cpp", recursive=True)
	for file in files:
		ok = 1
		for words in ng_words:
			if file.find(words) != -1:
				ok = 0
		if ok == 1:
			result.append(file)
		ok = 1
	return result

def make_cpp_json(target):
	sources = file_list()
	result = {}
	for source_name in sources:
		prefix = resolve_includes.prefix_name(source_name)
		result[prefix] = {}
		resolve_includes.make_cpp_list_wrap(source_name, result[prefix])
	json.dump(result, target, indent='\t')
	print('Made ' + str(len(result)) + ' snipetts')
	count = 1
	for pref in result:
		print(' ' + str(count) + '. ' + pref)
		count += 1

if __name__ == '__main__':
	res = {}
	target = resolve_includes.source_load('cpp.json', False)
	make_cpp_json(target)