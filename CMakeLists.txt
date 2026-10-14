cmake_minimum_required(VERSION 3.10)
project(libclirenderer CXX)

# Create a library target
add_library(libclirenderer
    include/libclirenderer/libclirenderer.h
    src/lcr-renderer.cpp
    src/lcr-system.cpp
)

# Specify where other projects can find its header files
target_include_directories(libclirenderer PUBLIC .)