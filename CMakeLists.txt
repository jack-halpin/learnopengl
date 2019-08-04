cmake_minimum_required (VERSION 2.6)
project (learnopengl)
# set the version number
set (learnopengl_VERSION_MAJOR 1)
set (learnopengl_VERSION_MINOR 0)

# set the source files
# set (SOURCES src/main.cpp src/glad.cpp)

# using file(GLOB...) we can have wildcard additions
file(GLOB SOURCES "src/*.cpp")

# add include directories
include_directories(include)

add_executable(learnopengl $(SOURCES)) 
