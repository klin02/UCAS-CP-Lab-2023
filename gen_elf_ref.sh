#!/bin/bash

# 指定目录和命令
asm_dir="asm_ref"
elf_dir="elf_ref"

# 遍历目录中的所有文件
for file in "$asm_dir"/*
do 
    base=${file##*/}
    base=${base%.*}
    elf=${elf_dir}/${base}
    if [ "$1" == "io" ]
    then
        LIB=./libcact
    else
        LIB=./cactio/${base}
    fi
    riscv64-unknown-elf-gcc -o $elf $file -L$LIB -lcactio
done
