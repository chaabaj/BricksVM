cmake_minimum_required(VERSION 2.6)

project($name)



file(GLOB_RECURSE SRCS "src/*.cpp")
file(GLOB_RECURSE HEADERS "include/*.hpp" "include/*.tpp")

if (UNIX OR APPLE)

	add_definitions("-std=c++11")
	
endif()

set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ../../../lib)

add_subdirectory(../../core ../../core_bin)

include_directories(include ../../core/include)

add_library($name SHARED $${SRCS} $${HEADERS})

target_link_libraries ($name bricksvm_core) 