#!/bin/bash

# 指定目录和命令
asm_dir="asm"
elf_dir="elf"

# 遍历目录中的所有文件
for file in "$asm_dir"/*
do 
    base=${file##*/}
    base=${base%.*}
    elf=${elf_dir}/${base}
    riscv64-unknown-elf-gcc -o $elf $file -L./libcact -lcactio
done