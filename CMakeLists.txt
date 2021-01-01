cmake_minimum_required (VERSION 2.6)
project (learnopengl)
# set the version number
set (learnopengl_VERSION_MAJOR 1)
set (learnopengl_VERSION_MINOR 0)

set (CMAKE_CXX_STANDARD 17)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/../bin)

# set the source files
set (GETSTARTED src/getting_started.cpp src/glad.cpp)
set (GETSTARTED1 src/getting_started1.cpp src/glad.cpp)
set (GETSTARTEDEX1 src/getting_started_ex1.cpp src/glad.cpp)
set (GETSTARTEDEX2 src/getting_started_ex2.cpp src/glad.cpp)
set (GETSTARTEDEX3 src/getting_started_ex3.cpp src/glad.cpp)
set (SHADERS src/shaders.cpp src/glad.cpp)
set (SHADERSEX1 src/shaders_ex1.cpp src/glad.cpp)
set (SHADERSEX2 src/shaders_ex2.cpp src/glad.cpp)
set (TEXTURES src/textures.cpp src/glad.cpp)
set (TEXTURESEX1 src/textures_ex1.cpp src/glad.cpp)
set (TEXTURESEX2 src/textures_ex2.cpp src/glad.cpp)
set (TEXTURESEX4 src/textures_ex4.cpp src/glad.cpp)
set (TRANSFORMS src/transforms.cpp src/glad.cpp)
set (TRANSFORMS2 src/transforms_ex2.cpp src/glad.cpp)
set (COORDS src/coord_sys.cpp src/glad.cpp)
# using file(GLOB...) we can have wildcard additions
#file(GLOB SOURCES "src/*.cpp")

if (UNIX)
    find_package(glfw3)
    set(GLFW_LIB glfw)
endif(UNIX)

if (WIN32)
    include_directories(../third_party/Include)
    link_directories(${CMAKE_BINARY_DIR}/../../third_party/Libs/GLFW)
    set(GLFW_LIB glfw3)
endif (WIN32)

# add include directories
include_directories(include)

# Getting started chapter
add_executable(getting_started.out "${GETSTARTED}") 
target_link_libraries(getting_started.out "${GLFW_LIB}")

# Getting started EBO
add_executable(getting_started1.out "${GETSTARTED1}")
target_link_libraries(getting_started1.out "${GLFW_LIB}")

# Getting started ex1
add_executable(getting_started_ex1.out "${GETSTARTEDEX1}")
target_link_libraries(getting_started_ex1.out "${GLFW_LIB}")

# Getting started ex2
add_executable(getting_started_ex2.out "${GETSTARTEDEX2}")
target_link_libraries(getting_started_ex2.out "${GLFW_LIB}")

# Getting started ex3
add_executable(getting_started_ex3.out "${GETSTARTEDEX3}")
target_link_libraries(getting_started_ex3.out "${GLFW_LIB}")

# Shaders chapter
add_executable(shaders_chapter.out "${SHADERS}")
target_link_libraries(shaders_chapter.out "${GLFW_LIB}")

# Shaders ex1
add_executable(shaders_ex1.out "${SHADERSEX1}")
target_link_libraries(shaders_ex1.out "${GLFW_LIB}")

add_executable(shaders_ex2.out "${SHADERSEX2}")
target_link_libraries(shaders_ex2.out "${GLFW_LIB}")

add_executable(textures_chapter.out "${TEXTURES}")
target_link_libraries(textures_chapter.out "${GLFW_LIB}")

add_executable(textures_ex1.out "${TEXTURESEX1}")
target_link_libraries(textures_ex1.out "${GLFW_LIB}")

add_executable(textures_ex2.out "${TEXTURESEX2}")
target_link_libraries(textures_ex2.out "${GLFW_LIB}")

add_executable(textures_ex4.out "${TEXTURESEX4}")
target_link_libraries(textures_ex4.out "${GLFW_LIB}")

add_executable(transforms_chapter.out "${TRANSFORMS}")
target_link_libraries(transforms_chapter.out "${GLFW_LIB}")

add_executable(transforms_ex2.out "${TRANSFORMS2}")
target_link_libraries(transforms_ex2.out "${GLFW_LIB}")

add_executable(coord_sys.out "${COORDS}")
target_link_libraries(coord_sys.out "${GLFW_LIB}")

message("System: ${CMAKE_SYSTEM_PREFIX_PATH}")

# find the include files for the glfw lib

# link to the glfw libs
message("lib: ${GLFW_LIB}")
