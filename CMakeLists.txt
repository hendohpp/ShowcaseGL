# cmake project configuration
cmake_minimum_required(VERSION 3.25)
project(
    ShowcaseGL
    VERSION 0.1.0
    DESCRIPTION "A small C++23 OpenGL framework for quickly creating scenes, loading assets, and testing shaders"
    LANGUAGES C CXX
)


# compiled binary location
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/bin")
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/lib")
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/lib")


# require c++23 and disable compiler specific flags
set(CMAKE_CXX_STANDARD              23)
set(CMAKE_CXX_STANDARD_REQUIRED     ON)
set(CMAKE_CXX_EXTENSIONS            OFF)


# require c11 and disable compiler specific flags
set(CMAKE_C_STANDARD            11)
set(CMAKE_C_STANDARD_REQUIRED   ON)
set(CMAKE_C_EXTENSIONS          OFF)


set(CMAKE_EXPORT_COMPILE_COMMANDS ON)


# downloading and building external dependencies
include(FetchContent)


# GLFW
set(GLFW_BUILD_DOCS         OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_EXAMPLES     OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_TESTS        OFF CACHE BOOL "" FORCE)
set(GLFW_VER                "3.5.1")

FetchContent_Declare(
    glfw
    GIT_REPOSITORY https://github.com/glfw/glfw.git
    GIT_TAG ${GLFW_VER}
    GIT_SHALLOW TRUE
)

FetchContent_MakeAvailable(glfw)


# GLAD
set(GLAD_SOURCE "${CMAKE_CURRENT_SOURCE_DIR}/external/glad/src/glad.c")

add_library(showcasegl_glad STATIC
    "${GLAD_SOURCE}"
)

target_compile_features(showcasegl_glad
    PRIVATE c_std_11
)

set_source_files_properties(
    "${GLAD_SOURCE}"
    PROPERTIES LANGUAGE C
)

target_include_directories(showcasegl_glad
    PUBLIC "${CMAKE_CURRENT_SOURCE_DIR}/external/glad/include"
)


# OpenGL
find_package(OpenGL REQUIRED)


# ShowcaseGL
add_library(showcasegl
    src/Application.cpp
    src/Camera.cpp
    src/Mesh.cpp
    src/Model.cpp
    src/Scene.cpp
    src/Shader.cpp
    src/Texture.cpp
)

target_compile_features(showcasegl
    PUBLIC cxx_std_23
)

target_include_directories(showcasegl
    PUBLIC "${CMAKE_CURRENT_SOURCE_DIR}/include"
)

target_link_libraries(showcasegl
    PUBLIC glfw showcasegl_glad OpenGL::GL
)

if(MSVC)
    target_compile_options(showcasegl PRIVATE
        /W4
        /permissive-
    )
else()
    target_compile_options(showcasegl PRIVATE
        -Wall
        -Wextra
    )
endif()


# developer tools
include(cmake/format.cmake)
include(cmake/tidy.cmake)


# usage examples
option(SHOWCASEGL_BUILD_EXAMPLES "Build ShowcaseGL examples" ON)

if(SHOWCASEGL_BUILD_EXAMPLES)
    add_subdirectory(examples)
endif()


# tests
option(SHOWCASEGL_BUILD_TESTS "build ShowcaseGL tests" ON)

if(SHOWCASEGL_BUILD_TESTS)
    enable_testing()
    add_subdirectory(tests)
endif()