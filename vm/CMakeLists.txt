cmake_minimum_required(VERSION 2.8)

project(bricksvm)

file(GLOB_RECURSE SRCS "src/*.cpp")
file(GLOB_RECURSE HEADERS "include/*.hpp" "include/*.tpp")

if (UNIX OR APPLE)

	target_link_libraries(pthread)
	add_definitions("-std=c++11")
	
endif()

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ../../bin)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ../../lib)
include_directories(include ../lib/gason/include)

add_executable(bricksvm ${SRCS} ${HEADERS})
install(TARGETS bricksvm DESTINATION ../bin)

if (WIN32)

	file(GLOB_RECURSE LIBRAIRIES "../lib/*.dll")
	
	add_custom_target(copy)
	MESSAGE( STATUS "DLL:" ${LIBRAIRIES} )
	foreach(Library ${LIBRAIRIES})
		add_custom_command(TARGET copy POST_BUILD
							COMMAND ${CMAKE_COMMAND} -E copy
							${Library} CMAKE_RUNTIME_OUTPUT_DIRECTORY)

	endforeach()
	
endif()

TARGET_LINK_LIBRARIES(bricksvm  ../../lib/gason/lib/gason)

