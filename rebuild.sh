#!/bin/bash

keep_file="CACT.g4"  # 指定要保留的文件
# keep_file="Example.g4"

# echo "Input Mode:"
# echo "  l      : Listener"
# echo "  v      : Visitor"
# echo "  default: Visitor"
# read choice

choice="l"
if [ "$choice" == "l" ];then
    echo "Mode: Listener"
    cp -r src_listener/ src/
else
    echo "Mode: Visitor"
    cp -r src_visitor/ src/
fi
# cp -r src_listener/ src/
cd grammar
find . ! -name "$keep_file" -type f -delete
if [ "$choice" == "l" ];then
    java -jar ../deps/antlr-4.8-complete.jar -Dlanguage=Cpp "$keep_file"
else
    java -jar ../deps/antlr-4.8-complete.jar -Dlanguage=Cpp -no-listener -visitor "$keep_file"
fi
cd ..
rm -rf build
mkdir build
cd build
cmake ..
make
cd ..
cp ./build/compiler ./
rm -rf src/