# Set min req version of Cmake
cmake_minimum_required(VERSION 3.10)

# Set project name
project(AT24Cx_Driver_Lib)

# Set our lib include directories
include_directories(src inc)

# Set the lib output folder
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ../lib)

# Create or our static library
ADD_LIBRARY( at24cx STATIC src/at24cx.c inc/at24cx.h )