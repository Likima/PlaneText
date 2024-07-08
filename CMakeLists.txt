cmake_minimum_required(VERSION 3.10)
project(Qil)

# Set C++ standard
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# Add source files
file(GLOB_RECURSE SOURCES "src/*.cpp")
file(GLOB_RECURSE SOURCES "src/Lexer/*.cpp")
file(GLOB_RECURSE SOURCES "src/Parser/*.cpp")

# Add executable
add_executable(${PROJECT_NAME} ${SOURCES})

