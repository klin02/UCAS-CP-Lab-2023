# !/bin/bash
if [@# == 0]
	echo "请指定特定分支";
	exit;

git checkout master
git merge $1

