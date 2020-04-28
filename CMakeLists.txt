cmake_minimum_required(VERSION 2.6)

project(test_phys-ci)

SET(CMAKE_CXX_FLAGS "-std=c++11 -O3")

include_directories(/home/travis/build/osrep/Runin)
include_directories(/home/travis/build/osrep/Runin/lib/googletest/googletest/include)

set(BINARY ${CMAKE_PROJECT_NAME})
file(GLOB_RECURSE SOURCES LIST_DIRECTORIES true *.h *.cpp)
set(SOURCES ${SOURCES})
add_executable(${BINARY}_run ${SOURCES})
add_library(${BINARY}_lib STATIC ${SOURCES})


add_subdirectory(/home/travis/build/osrep/Runin/lib/googletest)
add_subdirectory(/home/travis/build/osrep/Runin/tests)