cmake_minimum_required (VERSION 2.6)
project (learnopengl)
# set the version number
set (learnopengl_VERSION_MAJOR 1)
set (learnopengl_VERSION_MINOR 0)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/../bin)

# set the source files
# set (SOURCES src/main.cpp src/glad.cpp)

# using file(GLOB...) we can have wildcard additions
file(GLOB SOURCES "src/*.cpp")

#find_path(GLFW_INCLUDE_DIR
#    NAMES include
#    PATH_SUFFIXES "include" "glfw" "3.3"
#)
#message("glfw include: ${GLFW_INCLUDE_DIR}")
#find_library(GLFW_LIB glfw)

# add include directories
include_directories(include)

find_package(glfw3)



add_executable(helloTriangle.out ${SOURCES}) 
target_link_libraries(helloTriangle.out glfw)

message("System: ${CMAKE_SYSTEM_PREFIX_PATH}")

# find the include files for the glfw lib

# link to the glfw libs
message("lib: ${GLFW_LIB}")
