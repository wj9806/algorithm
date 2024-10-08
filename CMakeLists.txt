cmake_minimum_required(VERSION 3.7)

project(algorithm VERSION 1.0)
set(CMAKE_C_STANDARD 11)

include_directories(
        ${PROJECT_SOURCE_DIR}
        ${PROJECT_SOURCE_DIR}/src/data
        ${PROJECT_SOURCE_DIR}/src/tools
        ${PROJECT_SOURCE_DIR}/src/sort
)

file(GLOB_RECURSE SOURCE_LIST
        "tests/*.c"
        "src/data/*.c"
        "src/tools/*.c"
        "src/sort/*.c"
)

add_definitions(-DEN_DEBUG)

set(TEST_MODULE TEST_SORT)

option(${TEST_MODULE} "module should be tested" ON)

if(${TEST_MODULE} STREQUAL "ON")
    message("${TEST_MODULE} is defined")
    add_definitions(-D${TEST_MODULE})
else()
    message("${TEST_MODULE} is not defined")
endif()

add_executable(${PROJECT_NAME} ${SOURCE_LIST})