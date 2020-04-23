cmake_minimum_required(VERSION 2.6)
SET(CMAKE_CXX_FLAGS "-std=c++11 -O3")
# Locate GTest
find_package(GTest REQUIRED)
include_directories(${GTEST_INCLUDE_DIRS})
 
file(GLOB SRC_FILES ${PROJECT_SOURCE_DIR}/*.cpp)
include_directories(${PROJECT_SOURCE_DIR})
add_executable(runTests test_phys.cpp)
# Link runTests with what we want to test and the GTest and pthread library
add_library(runTests_lib ${SRC_FILES})
target_link_libraries(runTests runTests_lib)
target_link_libraries(runTests ${GTEST_LIBRARIES} pthread)

