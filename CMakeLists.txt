cmake_minimum_required(VERSION 2.6)

SET(CMAKE_CXX_FLAGS "-ggdb -O3 -fPIC -std=c++0x -march=native -mno-avx")

# Download and unpack googletest at configure time
configure_file(CMakeLists.txt.in googletest-download/CMakeLists.txt)
execute_process(COMMAND ${CMAKE_COMMAND} -G "${CMAKE_GENERATOR}" .
  RESULT_VARIABLE result
  WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}/googletest-download )
if(result)
  message(FATAL_ERROR "CMake step for googletest failed: ${result}")
endif()
execute_process(COMMAND ${CMAKE_COMMAND} --build .
  RESULT_VARIABLE result
  WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}/googletest-download )
if(result)
  message(FATAL_ERROR "Build step for googletest failed: ${result}")
endif()

# Add googletest directly to our build. This defines
# the gtest and gtest_main targets.
add_subdirectory(${CMAKE_CURRENT_BINARY_DIR}/googletest-src
                 ${CMAKE_CURRENT_BINARY_DIR}/googletest-build
                 EXCLUDE_FROM_ALL)

include_directories("${gtest_SOURCE_DIR}/include")


 
# Runin
file(GLOB SRC_FILES ${PROJECT_SOURCE_DIR}/*.cpp)

add_library(runTests_lib ${SRC_FILES})
add_executable(runTests test_phys.cpp)

target_link_libraries(runTests gtest_main pthread)
target_link_libraries(runTests runTests_lib)
enable_testing()