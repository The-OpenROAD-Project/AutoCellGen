# Specify the minimum version for CMake
cmake_minimum_required(VERSION 2.8)

# Message
message(STATUS "Transistor Placement")
message(STATUS ${CMAKE_CURRENT_SOURCE_DIR})
message(STATUS ${PROJECT_SOURCE_DIR})

# Find includes in the build directories
set(CMAKE_INCLUDE_CURRENT_DIR ON)

# Set CC and CXX
execute_process(COMMAND which gcc OUTPUT_VARIABLE CC OUTPUT_STRIP_TRAILING_WHITESPACE)
execute_process(COMMAND which g++ OUTPUT_VARIABLE CXX OUTPUT_STRIP_TRAILING_WHITESPACE)

set(CMAKE_C_COMPILER ${CC})
set(CMAKE_CXX_COMPILER ${CXX})

# Project's name
project(transistorplacement)

# build configuration - Debug|Release|RelWithDebInfo|MinSizeRel
set ( CMAKE_BUILD_TYPE Debug )

# Set the output folder where your program will be created
set(EXECUTABLE_OUTPUT_PATH ${CMAKE_BINARY_DIR})
set(LIBRARY_OUTPUT_PATH ${CMAKE_BINARY_DIR})

set(CMAKE_CXX_STANDARD 17)

set(PATH_SRC ${CMAKE_CURRENT_SOURCE_DIR}/src)

# Warnings/Errors

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Werror=return-type")

file(GLOB_RECURSE SRC_FILES_
	${PATH_SRC}/*.cpp
	${PATH_SRC}/*.c)

set(SRC_FILES ${SRC_FILES_})

# Include Directories
include_directories(headers ${PATH_SRC})

# Link library

# Targets
add_executable(placement ${SRC_FILES})
#add_executable(debug ${SRC_FILES})


# Linker Flags
#set_target_properties(main PROPERTIES LINK_FLAGS "-static -W1,--whole-archive -rdynamic -lpthread -W1,--no-whole-archive")
