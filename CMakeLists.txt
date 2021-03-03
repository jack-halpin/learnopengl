cmake_minimum_required (VERSION 2.6)
project (learnopengl)
# set the version number
set (learnopengl_VERSION_MAJOR 1)
set (learnopengl_VERSION_MINOR 0)

set (CMAKE_CXX_STANDARD 17)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/../bin)

set_property(GLOBAL PROPERTY USE_FOLDERS ON)

# set the source files
set (HELLO_TRIANGLE src/Hello_Triangle/hello_triangle.cpp src/glad.cpp)
set (HELLO_TRIANGLE_QUAD src/Hello_Triangle_QUAD/hello_triangle_quad.cpp src/glad.cpp)
set (HELLO_TRIANGLE_EX1 src/Hello_Triangle_EX1/hello_triangle_ex1.cpp src/glad.cpp)
set (HELLO_TRIANGLE_EX2 src/Hello_Triangle_EX2/hello_triangle_ex2.cpp src/glad.cpp)
set (HELLO_TRIANGLE_EX3 src/Hello_Triangle_EX3/hello_triangle_ex3.cpp src/glad.cpp)
set (SHADERS src/Shaders/shaders.cpp src/glad.cpp)
set (SHADERS_EX1 src/Shaders_EX1/shaders_ex1.cpp src/glad.cpp)
set (SHADERS_EX2 src/Shaders_EX2/shaders_ex2.cpp src/glad.cpp)
set (TEXTURES src/Textures/textures.cpp src/glad.cpp)
set (TEXTURES_EX1 src/Textures_EX1/textures_ex1.cpp src/glad.cpp)
set (TEXTURES_EX2 src/Textures_EX2/textures_ex2.cpp src/glad.cpp)
set (TEXTURES_EX4 src/Textures_EX4/textures_ex4.cpp src/glad.cpp)
set (TRANSFORMS src/Transformations/transforms.cpp src/glad.cpp)
set (TRANSFORMS_EX2 src/Transformations_EX2/transforms_ex2.cpp src/glad.cpp)
set (COORDS src/Coordinate_Systems/coordinate_systems.cpp src/glad.cpp)
set (CAMERA src/Camera/camera.cpp src/glad.cpp)
set (CAMERA_EX1 src/Camera_EX1/camera_ex1.cpp src/glad.cpp)
set (COLORS src/Colors/colors.cpp src/glad.cpp)
set (BASIC_LIGHTING src/Basic_Lighting/basic_lighting.cpp src/glad.cpp)
set (BASIC_LIGHTING_EX3 src/Basic_Lighting_EX3/basic_lighting_ex3.cpp src/glad.cpp)
set (MATERIALS src/Materials/materials.cpp src/glad.cpp)
set (LIGHTING_MAPS src/Lighting_Maps/lighting_maps.cpp src/glad.cpp)
set (LIGHT_CASTERS src/Light_Casters/light_casters.cpp src/glad.cpp)
set (MODEL src/Model/model.cpp src/glad.cpp src/mesh.cpp src/model.cpp)
set (SKELETAL_ANIMATION src/Skeletal_Animation/skeletal_animation.cpp src/glad.cpp src/mesh.cpp)
set (MULTIPLE_LIGHTS src/Multiple_Lights/multiple_lights.cpp src/glad.cpp)

# using file(GLOB...) we can have wildcard additions
#file(GLOB SOURCES "src/*.cpp")

if (UNIX)
    find_package(glfw3)
    set(GLFW_LIB glfw)
endif(UNIX)
if (WIN32)
    include_directories(../third_party/Include)
    link_directories(${CMAKE_BINARY_DIR}/../../third_party/Libs/GLFW)
    link_directories(${CMAKE_BINARY_DIR}/../../third_party/Libs/ASSIMP)
    set(GLFW_LIB glfw3)
    set(ASSIMP_LIB assimp-vc141-mt)
endif (WIN32)

# add include directories
include_directories(include)

# Getting started chapter
add_executable(hello_triangle "${HELLO_TRIANGLE}") 
target_link_libraries(hello_triangle "${GLFW_LIB}")

# Getting started EBO
add_executable(hello_triangle_quad "${HELLO_TRIANGLE_QUAD}")
target_link_libraries(hello_triangle_quad "${GLFW_LIB}")

# Getting started ex1
add_executable(hello_triangle_ex1 "${HELLO_TRIANGLE_EX1}")
target_link_libraries(hello_triangle_ex1 "${GLFW_LIB}")

# Getting started ex2
add_executable(hello_triangle_ex2 "${HELLO_TRIANGLE_EX2}")
target_link_libraries(hello_triangle_ex2 "${GLFW_LIB}")

# Getting started ex3
add_executable(hello_triangle_ex3 "${HELLO_TRIANGLE_EX3}")
target_link_libraries(hello_triangle_ex3 "${GLFW_LIB}")

# Shaders chapter
add_executable(shaders "${SHADERS}")
target_link_libraries(shaders "${GLFW_LIB}")

# Shaders ex1
add_executable(shaders_ex1 "${SHADERS_EX1}")
target_link_libraries(shaders_ex1 "${GLFW_LIB}")

add_executable(shaders_ex2 "${SHADERS_EX2}")
target_link_libraries(shaders_ex2 "${GLFW_LIB}")

add_executable(textures "${TEXTURES}")
target_link_libraries(textures "${GLFW_LIB}")

add_executable(textures_ex1 "${TEXTURES_EX1}")
target_link_libraries(textures_ex1 "${GLFW_LIB}")

add_executable(textures_ex2 "${TEXTURES_EX2}")
target_link_libraries(textures_ex2 "${GLFW_LIB}")

add_executable(textures_ex4 "${TEXTURES_EX4}")
target_link_libraries(textures_ex4 "${GLFW_LIB}")

add_executable(transforms "${TRANSFORMS}")
target_link_libraries(transforms "${GLFW_LIB}")

add_executable(transforms_ex2 "${TRANSFORMS_EX2}")
target_link_libraries(transforms_ex2 "${GLFW_LIB}")

add_executable(coordinate_systems "${COORDS}")
target_link_libraries(coordinate_systems "${GLFW_LIB}")

add_executable(camera "${CAMERA}")
target_link_libraries(camera "${GLFW_LIB}")

add_executable(camera_ex1 "${CAMERA_EX1}")
target_link_libraries(camera_ex1 "${GLFW_LIB}")

add_executable(colors "${COLORS}")
target_link_libraries(colors "${GLFW_LIB}")

add_executable(basic_lighting "${BASIC_LIGHTING}")
target_link_libraries(basic_lighting "${GLFW_LIB}")

add_executable(basic_lighting_ex3 "${BASIC_LIGHTING_EX3}")
target_link_libraries(basic_lighting_ex3 "${GLFW_LIB}")

add_executable(materials "${MATERIALS}")
target_link_libraries(materials "${GLFW_LIB}")

add_executable(lighting_maps "${LIGHTING_MAPS}")
target_link_libraries(lighting_maps "${GLFW_LIB}")

add_executable(light_casters "${LIGHT_CASTERS}")
target_link_libraries(light_casters "${GLFW_LIB}")

add_executable(model "${MODEL}")
target_link_libraries(model "${GLFW_LIB}" "${ASSIMP_LIB}")
add_custom_command(TARGET model PRE_BUILD COMMAND ${CMAKE_COMMAND} -E copy ../../third_party/Libs/ASSIMP/assimp-vc141-mt.dll $<TARGET_FILE_DIR:model>)

add_executable(skeletal_animation "${SKELETAL_ANIMATION}")
target_link_libraries(skeletal_animation "${GLFW_LIB}" "${ASSIMP_LIB}")
add_custom_command(TARGET skeletal_animation PRE_BUILD COMMAND ${CMAKE_COMMAND} -E copy ../../third_party/Libs/ASSIMP/assimp-vc141-mt.dll $<TARGET_FILE_DIR:skeletal_animation>)

add_executable(multiple_lights "${MULTIPLE_LIGHTS}")
target_link_libraries(multiple_lights "${GLFW_LIB}")

message("System: ${CMAKE_SYSTEM_PREFIX_PATH}")

# find the include files for the glfw lib

# link to the glfw libs
message("lib: ${GLFW_LIB}")