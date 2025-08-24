###############################
#                             #
# Copyright (c) 2022 Selenika #
#                             #
###############################

cmake_minimum_required(VERSION 3.10)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# set the project name
project(command-dispatcher-test)

include_directories(${CMAKE_SOURCE_DIR})

# add the executable
add_executable(command-dispatcher-test
        main.cpp
)
