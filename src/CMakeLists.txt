include_directories(${CMAKE_SOURCE_DIR}/include/xl)

file(GLOB_RECURSE SOURCES ${CMAKE_CURRENT_SOURCE_DIR}/*.cpp)

add_library(${PROJECT_NAME} SHARED ${SOURCES})
