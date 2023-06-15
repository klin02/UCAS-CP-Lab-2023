#!/bin/bash

# 指定目录和命令
# dir="samples/samples_lex_and_syntax"
# dir="samples/samples_semantic"
dir="samples/samples_codegen"
# dir="samples/extra_samples_pr1"
# dir="samples/extra_samples_pr2"

# gcc要求编译目标是.c文件，使用临时文件夹存储
tmp_dir="tmp"
out_dir="asm_ref/"

# 遍历目录中的所有文件

rm -rf $tmp_dir
mkdir $tmp_dir
for file in "$dir"/*
do
    # 检查文件是否存在
    if [ -f "$file" ]
    then
        base=${file##*/}
        base=${base%.*}
        tmp_c=${base}.c
        cp $file $tmp_dir/$tmp_c
    fi
done

for file in "$tmp_dir"/*
do 
    base=${file##*/}
    base=${base%.*}
    asm=${out_dir}${base}.S
    riscv64-unknown-elf-gcc -o $asm -S -c $file
done

rm -rf $tmp_dir