add_library(scriptlib STATIC scriptlib.c)
target_include_directories(scriptlib PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
target_link_libraries(scriptlib libdoomtools)
