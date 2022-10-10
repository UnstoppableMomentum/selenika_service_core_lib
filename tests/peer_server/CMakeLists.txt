###############################
#                             #
# Copyright (c) 2022 Selenika #
#                             #
###############################

cmake_minimum_required(VERSION 3.10)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(Boost_USE_STATIC_LIBS ON)
set(BIN_NAME selenika-peer-server)

# TODO
set(SELENIKA_PROJECT_ROOT_PATH /home/qaz/work/selenika/)
set(SELENIKA_PROJECT_LIB_CORE_PATH ${SELENIKA_PROJECT_ROOT_PATH}/selenika_service_core_lib/src)
set(SELENIKA_LIB_CORE_NAME selenika_service_core)

add_definitions(-DDEBUG)

# set the project name
project(${BIN_NAME})

include_directories(${CMAKE_SOURCE_DIR})
include_directories(${SELENIKA_PROJECT_LIB_CORE_PATH})

find_package(Boost 1.77.0 COMPONENTS log regex thread system REQUIRED)
find_package(OpenSSL)
find_package(Threads REQUIRED)

link_directories(/usr/local/bin)
# add the executable
add_executable(${BIN_NAME}
        main.cpp
)


target_link_libraries(${BIN_NAME} ${OPENSSL_LIBRARIES} -static-libgcc -static-libstdc++)
target_link_libraries(${BIN_NAME} ${Boost_LIBRARIES} -static-libgcc -static-libstdc++)
target_link_libraries(${BIN_NAME} ${CMAKE_THREAD_LIBS_INIT} -static-libgcc -static-libstdc++)


find_library(SELENIKA_LIB_CORE_PATH NAMES ${SELENIKA_LIB_CORE_NAME}  HINTS /usr/local/bin)

message("SELENIKA_LIB_CORE_PATH:" ${SELENIKA_LIB_CORE_PATH})

# TODO:
#if(${SELENIKA_LIB_CORE_PATH} EQUAL "SELENIKA_LIB_CORE_PATH-NOTFOUND")
#  message("Error! library " ${SELENIKA_LIB_CORE_NAME} " not found")        
#else


target_link_libraries(${BIN_NAME} ${SELENIKA_LIB_CORE_NAME} ${SELENIKA_LIB_CORE_PATH})


