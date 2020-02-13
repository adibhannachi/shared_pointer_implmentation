project(easymile_test)
cmake_minimum_required(VERSION 3.10.2)

add_executable(test_shared_ptr test_shared_ptr.cpp)

target_include_directories(test_shared_ptr PRIVATE ${CMAKE_SOURCE_DIR}/include)
