cmake_minimum_required(VERSION 3.0.0)
project(multigen VERSION 2.0)

foreach(SUBDIR cmdlib scriplib multigen)
  add_subdirectory("${SUBDIR}")

endforeach()
