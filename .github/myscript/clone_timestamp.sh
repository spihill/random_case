#!/bin/bash

git config --global user.name "spihill"
git config --global user.email "spihill.in@gmail.com"

if [[ $MY_GITHUB_ACTION_TEST ]]; then
	cd ../../test/
	mkdir .test
	cd .test
	git clone https://spihill:$CPP_JSON_GIST_TOKEN@gist.github.com/spihill/$TIMESTAMP_GIST_ID
	mv $TIMESTAMP_GIST_ID timestamp
fi