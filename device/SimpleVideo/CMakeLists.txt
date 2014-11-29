cmake_minimum_required(VERSION 2.8)

project(SimpleVideo)
file(GLOB_RECURSE SRCS "src/*.cpp")
file(GLOB_RECURSE HEADERS "include/*.hpp" "include/*.tpp")

if (UNIX OR APPLE)

	add_definitions("-std=c++11 -Wall -I /usr/local/include/SDL2")
	set(CMAKE_SHARED_LINKER_FLAGS "-lSDL2 -lSDL2_ttf")
endif()


set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ../../../lib)

add_subdirectory(../../core ../../core_bin)

include_directories(include ../../core/include)

add_library(SimpleVideo SHARED ${SRCS} ${HEADERS})

target_link_libraries (SimpleVideo bricksvm_core ${CMAKE_THREAD_LIBS_INIT} ${CMAKE_DL_LIBS})