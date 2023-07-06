#!/bin/bash

# 指定目录
dir="samples/samples_codegen"
# gcc要求编译目标是.c文件，使用临时文件夹存储
tmp_dir="tmp"
out_dir="asm_ref/"

# 优化等级
if [ "$1" == "O2" ] || [ "$1" == "O1" ] || [ "$1" == "O0" ]
then
    OPTIM_LEVEL=$1
elif [ "$1" == "" ]
then
    OPTIM_LEVEL="O0"
else
    echo "Illegal OPTIM arg: $1"
    exit
fi
echo "OPTIM_LEVEL: $OPTIM_LEVEL"

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
    riscv64-unknown-elf-gcc -o $asm -fPIC -$OPTIM_LEVEL -S -c $file
done

rm -rf $tmp_dir