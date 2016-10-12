cmake_minimum_required(VERSION 3.6)
project(handleflow)

set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -Werror")

set(SOURCE_FILES main.c )
add_executable(main ${SOURCE_FILES})

include_directories( ${CMAKE_CURRENT_SOURCE_DIR})

#set(CMAKE_VERBOSE_MAKEFILE on)