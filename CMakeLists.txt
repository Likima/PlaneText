cmake_minimum_required(VERSION 3.10)
project(Qil)

# Set C++ standard
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# Set build type to Debug
set(CMAKE_BUILD_TYPE Debug)

# Add source files
file(GLOB_RECURSE SOURCES "src/*.cpp")
file(GLOB_RECURSE LEXER_SOURCES "src/Lexer/*.cpp")
file(GLOB_RECURSE PARSER_SOURCES "src/Parser/*.cpp")

# Combine all source files
list(APPEND SOURCES ${LEXER_SOURCES})
list(APPEND SOURCES ${PARSER_SOURCES})

# Add executable
add_executable(${PROJECT_NAME} ${SOURCES})
