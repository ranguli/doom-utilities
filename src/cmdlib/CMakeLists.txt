add_library(cmdlib STATIC cmdlib.c)
target_include_directories(cmdlib PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
