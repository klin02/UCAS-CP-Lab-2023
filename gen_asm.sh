#!/bin/bash

# 指定目录
dir="samples/samples_codegen"
out_dir="asm"

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
for file in "$dir"/*
do
    # 检查文件是否存在
    if [ -f "$file" ]
    then
        ./compiler -$OPTIM_LEVEL $file
        base=${file##*/}
        base=${base%.*}
        asm=${base}.S
        mv $asm $out_dir/$asm
    fi
done
