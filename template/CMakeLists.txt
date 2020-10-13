# Set min req version of Cmake
cmake_minimum_required(VERSION 3.10)

# Set project name
project(AT24Cx_Example_Main)

# Set our lib include directories
include_directories(../inc)

# Create the C Executable
add_executable(at24cx main.c)
# Link against our at24cx lib
TARGET_LINK_LIBRARIES(at24cx "${CMAKE_SOURCE_DIR}/../lib/libat24cx.a")
