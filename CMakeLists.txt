cmake_minimum_required(VERSION 3.1)
project("awful")

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${PROJECT_SOURCE_DIR})

#Tree shaking
file(GLOB_RECURSE ENGINE_SRC_FILES
    ${PROJECT_SOURCE_DIR}/src/awful/*.c)

file(GLOB_RECURSE TESTBED_SRC_FILES
${PROJECT_SOURCE_DIR}/src/testbed/*.c)

file(GLOB_RECURSE SH3D_SRC_FILES
${PROJECT_SOURCE_DIR}/src/sh3d/*.c)

include_directories(${PROJECT_NAME}
${PROJECT_SOURCE_DIR}/include)

add_executable(game ${ENGINE_SRC_FILES} ${TESTBED_SRC_FILES})
add_executable(sh3d ${ENGINE_SRC_FILES} ${SH3D_SRC_FILES})

target_link_libraries(game m)