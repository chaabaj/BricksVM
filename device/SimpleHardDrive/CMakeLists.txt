cmake_minimum_required(VERSION 2.6)

project(SimpleHardDrive)



file(GLOB_RECURSE SRCS "src/*.cpp")
file(GLOB_RECURSE HEADERS "include/*.hpp" "include/*.tpp")

if (UNIX OR APPLE)

	add_definitions("-std=c++11 -Wall -ggdb")
	
endif()

set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ../../../lib)

add_subdirectory(../../core ../../core_bin)

include_directories(include ../../core/include)

add_library(SimpleHardDrive SHARED ${SRCS} ${HEADERS})

target_link_libraries (SimpleHardDrive bricksvm_core ${CMAKE_THREAD_LIBS_INIT} ${CMAKE_DL_LIBS})