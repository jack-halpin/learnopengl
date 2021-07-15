cmake_minimum_required (VERSION 2.6)
project (learnopengl)
# set the version number
set (learnopengl_VERSION_MAJOR 1)
set (learnopengl_VERSION_MINOR 0)

set (CMAKE_CXX_STANDARD 17)
if(WIN32)
	set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/bin)
endif(WIN32)

set_property(GLOBAL PROPERTY USE_FOLDERS ON)

if (UNIX)
    include_directories(../third_party/glfw/include)
    include_directories(../third_party/assimp-5.0.1/include)
    link_directories(/usr/local/lib)

    find_package(glfw3)
    set(LIBS glfw assimp)
endif(UNIX)
if (WIN32)
    include_directories(../third_party/Include)
    link_directories(${CMAKE_BINARY_DIR}/../../third_party/Libs/GLFW)
    link_directories(${CMAKE_BINARY_DIR}/../../third_party/Libs/ASSIMP)
    set(LIBS glfw3 assimp-vc141-mt)
endif (WIN32)

include_directories(include)


# Declare Chapters
set(CHAPTERS
    1.Getting_Started
    2.Lighting
    3.Model_Loading
    4.Advanced_OpenGL
    7.In_Practice
)

# Getting Started
set(1.Getting_Started
    1.1.Hello_Triangle
    1.2.Hello_Triangle_QUAD
    1.3.Hello_Triangle_EX1
    1.4.Hello_Triangle_EX2
    1.5.Hello_Triangle_EX3
    2.1.Shaders
    2.2.Shaders_EX1
    2.3.Shaders_EX2
    3.1.Textures
    3.2.Textures_EX1
    3.3.Textures_EX2
    3.4.Textures_EX4
    4.1.Transformations
    4.2.Transformations_EX2
    5.1.Coordinate_Systems
    6.1.Camera
    6.2.Camera_EX1
)

# Lighting
set (2.Lighting
    1.1.Colors
    2.1.Basic_Lighting
    2.2.Basic_Lighting_EX3
    3.1.Materials
    4.1.Lighting_Maps
    5.1.Light_Casters
    6.1.Multiple_Lights
)

# Model Loading
set(3.Model_Loading
    1.1.Model
    2.1.Skeletal_Animation
)

# Advanced
set(4.Advanced_OpenGL
    1.1.Depth_Testing
    2.1.Stencil_Testing
)

# In Practice
set (7.In_Practice
    Breakout
)

foreach (CHAPTER ${CHAPTERS})
    foreach (DEMO ${${CHAPTER}})
        file(GLOB SOURCE
            "src/${CHAPTER}/${DEMO}/*.h"
            "src/${CHAPTER}/${DEMO}/*.cpp"
            "src/${CHAPTER}/${DEMO}/*.vs"
            "src/${CHAPTER}/${DEMO}/*.fs"
            "src/${CHAPTER}/${DEMO}/*.gs"
            "src/glad.cpp"
        )

        # Setup source groups
        file (GLOB SHADERS
            "src/${CHAPTER}/${DEMO}/*.vs"
            "src/${CHAPTER}/${DEMO}/*.fs"
        )
        file (GLOB_RECURSE HEADERS
            "include/*.h"
        )
        source_group("Shaders" FILES ${SHADERS})
        source_group(TREE ${CMAKE_CURRENT_SOURCE_DIR} FILES ${HEADERS})


        set(NAME "${DEMO}")
        add_executable(${NAME} ${SOURCE} ${HEADERS})
        target_link_libraries(${NAME} ${LIBS})

        set_target_properties (${NAME} PROPERTIES
            FOLDER ${CHAPTER}
        )

    endforeach(DEMO)
endforeach(CHAPTER)