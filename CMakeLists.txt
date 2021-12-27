cmake_minimum_required(VERSION 3.1)
project("awful")

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${PROJECT_SOURCE_DIR})

#Tree shaking
file(GLOB_RECURSE SRC_FILES
    ${PROJECT_SOURCE_DIR}/src/*.c)

message("${SRC_FILES}")

include_directories(${PROJECT_NAME} ${PROJECT_SOURCE_DIR}/include)

add_executable(${PROJECT_NAME} ${SRC_FILES})
