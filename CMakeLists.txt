cmake_minimum_required(VERSION 3.0)
project(cjinja)

set(TEST_NAME cjinja_test)
add_subdirectory(deps/ejson)
include_directories(. deps/ejson/include)

add_library(${PROJECT_NAME} cjinja.cpp)

add_executable(${TEST_NAME} cjinja.cpp test/test.cpp)
target_link_libraries(${TEST_NAME} ejson)