#!/bin/bash
read_dir_file(){
for file in `ls $1`  # $1 是函数传进的参数
do
 if [ -d $1"/"$file ]   # -d判断是否是目录
 then
	read_dir_file $1"/"$file
 else  #  在else部分处理文件
	git update-index --skip-worktree $1"/"$file
 fi
done
}

cd ../
read_dir_file deps/antlr4-runtime/dist
read_dir_file deps/antlr4-runtime/build
