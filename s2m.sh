# !/bin/bash
if [@# == 0];then
	echo "请指定特定分支";
	exit;
fi

git checkout master
git merge $1

