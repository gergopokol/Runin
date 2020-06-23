cmake_minimum_required(VERSION 3.1)

project(Runin VERSION 1.8.2
              LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 11)

# TODO check flags to use
set(CMAKE_CXX_FLAGS "-Wall -ggdb -O3 -fPIC -march=native -mno-avx")

include_directories("include")

add_subdirectory(src)

option(RUNIN_ENABLE_TESTS "Enable tests" OFF)

if (RUNIN_ENABLE_TESTS)
    add_subdirectory(test)
endif()
