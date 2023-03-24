# !/bin/bash
if [ -z $1];then
	echo "请指定特定分支"
	exit
fi

git checkout master
git pull origin master
git checkout $1
git merge master
git push origin $1

