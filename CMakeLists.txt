cmake_minimum_required(VERSION 2.6)

#SET(CMAKE_CXX_FLAGS "-std=c++11 -O3 -lgcov --coverage" )
#SET(CMAKE_EXE_LINKER_FLAGS_INIT "-lgcov --coverage")
set (CMAKE_SHARED_LINKER_FLAGS "-lgcov --coverage")
SET(CMAKE_CXX_FLAGS "-ggdb -O3 -fPIC -std=c++0x -march=native -mno-avx")

# Locate GTest
add_compile_options(-std=c++11 -lgcov --coverage)
include_directories(/home/travis/build/osrep/Runin/ext/googletest/googletest/include/)
 
file(GLOB SRC_FILES ${PROJECT_SOURCE_DIR}/*.cpp)
include_directories(${PROJECT_SOURCE_DIR}/*.h)

add_library(runTests_lib ${SRC_FILES})
add_executable(runTests test_phys.cpp)

set(GTEST_LIBRARY "/home/travis/build/osrep/Runin/lib/libgtest.a")
set(GTEST_MAIN_LIBRARY "/home/travis/build/osrep/Runin/lib/libgtest_main.a")

target_link_libraries(runTests ${GTEST_LIBRARY} ${GTEST_MAIN_LIBRARY} pthread)
target_link_libraries(runTests runTests_lib)
enable_testing()