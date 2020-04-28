cmake_minimum_required(VERSION 2.6)
SET(CMAKE_CXX_FLAGS "-std=c++11 -O3")
# Locate GTest

set(GTEST_ROOT "/home/travis/build/osrep/Runin/DEPS" CACHE PATH "Path to googletest")
find_package(GTest REQUIRED)
include_directories(${GTEST_INCLUDE_DIRS})
 
file(GLOB SRC_FILES ${PROJECT_SOURCE_DIR}/*.cpp)
include_directories(${PROJECT_SOURCE_DIR}/*.h)

add_library(runTests_lib ${SRC_FILES})
add_executable(runTests test_phys.cpp)

target_link_libraries(runTests ${GTEST_LIBRARIES} pthread)
target_link_libraries(runTests runTests_lib)
enable_testing()

