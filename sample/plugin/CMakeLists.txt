file(GLOB_RECURSE SOURCES ${CMAKE_CURRENT_SOURCE_DIR}/*.cpp)
add_library(plugin_sample SHARED ${SOURCES})
target_link_libraries(plugin_sample xl)
