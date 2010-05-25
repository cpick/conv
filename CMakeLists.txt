cmake_minimum_required(VERSION 2.6)

#project

project(CONV)
#set(CMAKE_VERBOSE_MAKEFILE ON)

#dependencies

FIND_PACKAGE(Curses)

#build

CONFIGURE_FILE(${CMAKE_CURRENT_SOURCE_DIR}/config.h.in
        ${CMAKE_CURRENT_BINARY_DIR}/config.h)

include_directories(${CMAKE_CURRENT_SOURCE_DIR} ${CMAKE_CURRENT_BINARY_DIR}
        ${CURSES_INCLUDE_DIR})

set(CMAKE_C_FLAGS "-Wall -W")
set(CMAKE_C_FLAGS_DEBUG "-g")

set(CONV_SRCS "conv.c")
set(CONV_LIBS ${CURSES_LIBRARIES})

add_executable(conv ${CONV_SRCS})
target_link_libraries(conv ${CONV_LIBS})
