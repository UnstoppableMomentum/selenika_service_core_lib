###############################
#                             #
# Copyright (c) 2022 Selenika #
#                             #
###############################

cmake_minimum_required(VERSION 3.10)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(BIN_NAME selenika_service_core)

add_definitions(-DDEBUG)

# set the project name
project(${BIN_NAME})

include_directories(${CMAKE_SOURCE_DIR})

find_package(Boost 1.77.0 COMPONENTS log regex program_options thread system REQUIRED)
find_package(OpenSSL)
find_package(Threads REQUIRED)

add_library(${BIN_NAME} SHARED
    command_dispatcher/command_dispatcher_base.cpp
    command_line/cmd_line_options.cpp
    config/logging.cpp
    messaging/message_processing_data.cpp
    messaging/response.cpp
    server/ssh_websocket_server.cpp
    system/system_utils.cpp
    websocket/listener.cpp
    websocket/request_handler.cpp
    websocket/sessions.cpp
    websocket/websocket_session.cpp)

# TODO provide flag for static linking
target_link_libraries(${BIN_NAME} ${OPENSSL_LIBRARIES} -static-libgcc -static-libstdc++)
target_link_libraries(${BIN_NAME} ${Boost_LIBRARIES} -static-libgcc -static-libstdc++)
target_link_libraries(${BIN_NAME} ${CMAKE_THREAD_LIBS_INIT} -static-libgcc -static-libstdc++)

install(TARGETS ${BIN_NAME} DESTINATION bin)
