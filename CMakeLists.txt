cmake_minimum_required(VERSION 2.6)
 
# Locate GTest
find_package(GTest REQUIRED)
include_directories(${GTEST_INCLUDE_DIRS})
 
#file(GLOB SRC_FILES ${PROJECT_SOURCE_DIR}/*.cpp)
#list(REMOVE_ITEM SRC_FILES ${PROJECT_SOURCE_DIR}/main.cpp)
 
# Link runTests with what we want to test and the GTest and pthread library
#add_library(runTests_lib ${SRC_FILES})
add_executable(runTests tests.cpp)
target_link_libraries(runTests ${GTEST_LIBRARIES} pthread)