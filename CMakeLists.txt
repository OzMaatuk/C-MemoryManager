cmake_minimum_required(VERSION 2.8.9)

project (CPP_EX3)                  # name of the project

set(CMAKE_CXX_FLAGS "-std=c++11")          # flags  

set(CMAKE_BUILD_TYPE Release)              # build type

include_directories(headers)               # additional files

#include_directories(Files)                # additional files

file(GLOB SOURCES "src/*.cpp")             # source files

add_executable(run_mm.o ${SOURCES})      # compiling

install(TARGETS run_mm.o DESTINATION .)  # install the cmake


# to run do -> cmake ../.
# and then -> make