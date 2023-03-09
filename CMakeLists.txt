cmake_minimum_required(VERSION 3.5)

project(Compiler LANGUAGES CXX)

set(CMAKE_BUILD_TYPE "Debug")
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

include_directories(deps/antlr4-runtime/runtime/src)
include_directories(grammar)
include_directories(src)

link_directories("deps/antlr4-runtime/dist")
link_libraries(antlr4-runtime)

FILE(GLOB SOURCE_FILES "src/*.cpp" "grammar/*.cpp")

add_definitions(-w -g)
add_executable(compiler ${SOURCE_FILES})
