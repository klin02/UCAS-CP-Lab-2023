keep_file="CACT.g4"  # 指定要保留的文件

cd grammar
find . ! -name "$keep_file" -type f -delete
java -jar ../deps/antlr-4.8-complete.jar -Dlanguage=Cpp -no-listener -visitor "$keep_file"
cd ..
rm -rf build
mkdir build
cd build
cmake ..
make
cd ..
cp ./build/compiler ./
