cmake_minimum_required(VERSION 2.6)

#project

project(CONV)
#set(CMAKE_VERBOSE_MAKEFILE ON)

#build

set(CMAKE_C_FLAGS "-Wall -W")
set(CMAKE_C_FLAGS_DEBUG "-g")

set(CONV_SRCS "conv.c")

add_executable(conv ${CONV_SRCS})
