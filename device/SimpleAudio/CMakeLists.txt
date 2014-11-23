cmake_minimum_required(VERSION 2.6)

project(SimpleAudio)



file(GLOB_RECURSE SRCS "src/*.cpp")
file(GLOB_RECURSE HEADERS "include/*.hpp" "include/*.tpp")

if (UNIX OR APPLE)

	add_definitions("-std=c++11 -Wall -ggdb")
	set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} -lsfml-system -lsfml-audio")
	
endif()

set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ../../../lib)

add_subdirectory(../../core ../../core_bin)

include_directories(include ../../core/include)

add_library(SimpleAudio SHARED ${SRCS} ${HEADERS})

target_link_libraries (SimpleAudio bricksvm_core ${CMAKE_THREAD_LIBS_INIT} ${CMAKE_DL_LIBS})