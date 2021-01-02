add_library(scriplib STATIC scriplib.c)
target_include_directories(scriplib PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
target_link_libraries(scriplib cmdlib)
