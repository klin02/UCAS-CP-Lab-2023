#!/bin/bash

# 指定目录和命令
# dir="samples/samples_lex_and_syntax"
dir="samples/samples_semantic"
# dir="samples/extra_samples_pr1"
# dir="samples/extra_samples_pr2"
command="./compiler"

total_cnt=0
pass_cnt=0
fail_list=()
# 遍历目录中的所有文件
for file in "$dir"/*
do
    # 检查文件是否存在
    if [ -f "$file" ]
    then
        echo ">>> Test on file: $file"
        
        ((total_cnt=total_cnt+1))
        # 执行命令并获取输出信息和返回值
        output=$(eval "$command \"$file\"")
        exit_code=$?

        # 打印输出信息和返回值
        echo ">>>> Output:"
        echo "$output"
        echo ">>>> Exit code: $exit_code"

        if [ $exit_code -ne 0 ] && [[ $file == *"false"* ]]
        then
                echo "Pass"
                ((pass_cnt=pass_cnt+1))
        elif [ $exit_code -eq 0 ] && [[ $file == *"true"* ]]
        then 
                echo "Pass"
                ((pass_cnt=pass_cnt+1))
        else
                echo "Fail"
                substr=$(echo $file | awk -F"/" '{print $NF}' | awk -F"_" '{print $1}')
                fail_list+=($substr)
        fi
        echo -e "\n"
    fi
done

echo "Fail list: ${fail_list[@]}"
echo "Pass rate: $pass_cnt / $total_cnt "