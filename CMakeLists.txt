# author: Chris Pick <conv@chirspick.com>
# license: (C) 2010 Chris Pick, all rights reserved.

cmake_minimum_required(VERSION 2.6)

# project

project(conv)
set(CMAKE_VERBOSE_MAKEFILE OFF)

# dependencies

FIND_PACKAGE(Curses)

# build

configure_file(${CMAKE_CURRENT_SOURCE_DIR}/config.h.in
        ${CMAKE_CURRENT_BINARY_DIR}/config.h)

include_directories(${CMAKE_CURRENT_SOURCE_DIR} ${CMAKE_CURRENT_BINARY_DIR}
        ${CURSES_INCLUDE_DIR})

set(CMAKE_C_FLAGS "-Wall -W")
set(CMAKE_C_FLAGS_DEBUG "-g")

set(conv_SRCS "conv.c")
set(conv_LIBS ${CURSES_LIBRARIES})

add_executable(conv ${conv_SRCS})
target_link_libraries(conv ${conv_LIBS})
