cmake_minimum_required(VERSION 3.2)
project(rapidjson_example)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

include_directories(/usr/local/include)

set(SOURCE_FILES main.cpp value_check.cpp read_write.cpp simple_checker.cpp simple_checker.h)
add_executable(rapidjson_example ${SOURCE_FILES})