cmake_minimum_required(VERSION 2.6)

project(bricksvm_core)

file(GLOB_RECURSE SRCS "src/*.cpp")
file(GLOB_RECURSE HEADERS "include/*.hpp" "include/*.tpp")

if (UNIX OR APPLE)

	target_link_libraries(pthread)
	add_definitions("-std=c++11")
	
endif()

find_package (Threads)


set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ../../lib)

include_directories(include)

add_library(bricksvm_core SHARED ${SRCS} ${HEADERS})


TARGET_LINK_LIBRARIES(bricksvm_core ${CMAKE_THREAD_LIBS_INIT} ${CMAKE_DL_LIBS})