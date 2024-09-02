############################################################################
## BSD 3-Clause License
##
## Copyright (c) 2024, Kyeonghyeon Baek, Sehyeon Chung, Handong Cho, 
## Hyunbae Seo, Kyu-myung Choi, and Taewhan Kim
## All rights reserved.
##
## Redistribution and use in source and binary forms, with or without
## modification, are permitted provided that the following conditions are met:
##
## 1. Redistributions of source code must retain the above copyright notice, this
##    list of conditions and the following disclaimer.
##
## 2. Redistributions in binary form must reproduce the above copyright notice,
##    this list of conditions and the following disclaimer in the documentation
##    and/or other materials provided with the distribution.
##
## 3. Neither the name of the copyright holder nor the names of its
##    contributors may be used to endorse or promote products derived from
##    this software without specific prior written permission.
##
## THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
## AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
## IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
## DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE
## FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
## DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR
## SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER
## CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY,
## OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
## OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
############################################################################

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
