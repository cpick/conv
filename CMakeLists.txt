# author: Chris Pick <conv@chrispick.com>
# license:
#
# Copyright 2010 Chris Pick. All rights reserved.
#
# Redistribution and use in source and binary forms, with or without
# modification, are permitted provided that the following conditions are met:
#
#    1. Redistributions of source code must retain the above copyright
#       notice, this list of conditions and the following disclaimer.
#
#    2. Redistributions in binary form must reproduce the above copyright
#       notice, this list of conditions and the following disclaimer in the
#       documentation and/or other materials provided with the distribution.
#
# THIS SOFTWARE IS PROVIDED BY CHRIS PICK ``AS IS'' AND ANY EXPRESS OR IMPLIED
# WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF
# MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO
# EVENT SHALL CHRIS PICK OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT,
# INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT
# NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
# DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
# THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
# (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF
# THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
#
# The views and conclusions contained in the software and documentation are
# those of the authors and should not be interpreted as representing official
# policies, either expressed or implied, of Chris Pick.

cmake_minimum_required(VERSION "2.8")

# project

project(conv "C")

# settings

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

# dependencies

find_package(Curses)

# configuration

configure_file("${CMAKE_CURRENT_SOURCE_DIR}/config.h.in"
        "${CMAKE_CURRENT_BINARY_DIR}/config.h")

# build

add_executable(conv "conv.c")
target_compile_options(conv PRIVATE "-Wall" "-W")
target_include_directories(conv PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}
        ${CMAKE_CURRENT_BINARY_DIR} ${CURSES_INCLUDE_DIR})
target_link_libraries(conv PRIVATE ${CURSES_LIBRARIES})

# install

install(TARGETS conv DESTINATION "bin")
