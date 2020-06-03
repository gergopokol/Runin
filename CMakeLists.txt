cmake_minimum_required(VERSION 2.6)

SET(CMAKE_CXX_FLAGS "-std=c++11 -O3")
# Locate GTest

include_directories(${PROJECT_SOURCE_DIR}/googletest/googletest/include/)
 
file(GLOB SRC_FILES ${PROJECT_SOURCE_DIR}/*.cpp)
include_directories(${PROJECT_SOURCE_DIR}/*.h)

add_library(runTests_lib ${SRC_FILES})
add_executable(runTests test_phys.cpp)

set(GTEST_LIBRARY "${PROJECT_SOURCE_DIR}/lib/libgtest.a")
set(GTEST_MAIN_LIBRARY "${PROJECT_SOURCE_DIR}/lib/libgtest_main.a")

target_link_libraries(runTests ${GTEST_LIBRARY} ${GTEST_MAIN_LIBRARY} pthread)
target_link_libraries(runTests runTests_lib)
enable_testing()
