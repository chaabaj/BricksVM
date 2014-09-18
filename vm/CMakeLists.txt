cmake_minimum_required(VERSION 2.8)

project(bricksvm)

file(GLOB_RECURSE SRCS "src/*.cpp")
file(GLOB_RECURSE HEADERS "include/*.hpp" "include/*.tpp")

if (UNIX OR APPLE)

	target_link_libraries(pthread)
	add_definitions("-std=c++11")
	
endif()

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ../../bin)

include_directories(include ../core/include)
target_link_libraries (bricksvm bricksvm_core) 

add_executable(bricksvm ${SRCS} ${HEADERS})
install(TARGETS bricksvm DESTINATION ../bin)

