cmake_minimum_required(VERSION 2.6)

SET(CMAKE_CXX_FLAGS "-std=c++11 -O3")
# Locate GTest

include_directories(${GTEST_INCLUDE_DIRS})
 
file(GLOB SRC_FILES ${PROJECT_SOURCE_DIR}/*.cpp)
include_directories(${PROJECT_SOURCE_DIR}/*.h)

add_library(runTests_lib ${SRC_FILES})
add_executable(runTests test_phys.cpp)

target_link_libraries(runTests /home/travis/build/osrep/Runin/lib/*.a pthread)
target_link_libraries(runTests runTests_lib)
enable_testing()
