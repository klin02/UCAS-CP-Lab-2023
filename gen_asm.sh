#!/bin/bash

# 指定目录
# dir="samples/samples_lex_and_syntax"
# dir="samples/samples_semantic"
dir="samples/samples_codegen"
# dir="samples/extra_samples_pr1"
# dir="samples/extra_samples_pr2"

out_dir="asm_gen/"

# 遍历目录中的所有文件

for file in "$dir"/*
do
    # 检查文件是否存在
    if [ -f "$file" ]
    then
        ./compiler $file
        base=${file##*/}
        base=${base%.*}
        asm=${base}.S
        mv $base $out_dir/$asm
    fi
done
