project(easymile_test)
cmake_minimum_required(VERSION 3.10.2)

add_library(shared_ptr main.cpp)
add_executable(bin main.cpp )
