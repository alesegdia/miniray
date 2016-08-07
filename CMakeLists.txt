cmake_minimum_required(VERSION 2.6)
project(tortas)

set(CMAKE_MODULE_PATH "${CMAKE_SOURCE_DIR}/cmake" ${CMAKE_MODULE_PATH})
set(CML_DIR "~/Libs/cml-1_0_3")
list(APPEND CMAKE_CXX_FLAGS "-m64 -static -std=c++0x ${CMAKE_CXX_FLAGS} -g -ftest-coverage -fprofile-arcs")

add_subdirectory(src/game)
