cmake_minimum_required(VERSION 3.20)

project(vkdss VERSION 1.0 LANGUAGES CXX)

# Require C++20
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED True)
set(CMAKE_CXX_EXTENSIONS False)

# Define the executable
add_executable(vkdss main.cpp)

add_custom_command(TARGET vkdss POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy
        "${CMAKE_SOURCE_DIR}/bcsstk01.mtx"
        "$<TARGET_FILE_DIR:vkdss>/bcsstk01.mtx"
)