cmake_minimum_required(VERSION 2.8)

project(bricksvm)

file(GLOB_RECURSE SRCS "src/*.cpp")
file(GLOB_RECURSE HEADERS "include/*.hpp" "include/*.tpp")

if (UNIX OR APPLE)

	set(CMAKE_CXX_FLAGS "-std=c++11 -ggdb -Wall -pthread")
	
endif()

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ../../bin)

include_directories(include ../core/include)

add_executable(bricksvm ${SRCS} ${HEADERS})
install(TARGETS bricksvm DESTINATION ../bin)

target_link_libraries (bricksvm bricksvm_core ${CMAKE_THREAD_LIBS_INIT} ${CMAKE_DL_LIBS}) 
