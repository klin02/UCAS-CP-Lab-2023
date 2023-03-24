#!/bin/bash
if [ -z "$1" ];then
	echo "请指定特定分支"
	exit
fi

git checkout master
git merge $1

