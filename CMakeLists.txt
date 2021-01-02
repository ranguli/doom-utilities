cmake_minimum_required(VERSION 3.0.0)
project(doom-utitiles VERSION 1.0)

foreach(SUBDIR cmdlib scriplib multigen)
    add_subdirectory("${SUBDIR}")
endforeach()
