cmake_minimum_required(VERSION 3.20)

project(physics_simulator VERSION 1.0 LANGUAGES C CXX)

include(FetchContent)

# Disable unnecessary GLFW features
set(GLFW_BUILD_DOCS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_TESTS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_EXAMPLES OFF CACHE BOOL "" FORCE)
set(GLFW_INSTALL OFF CACHE BOOL "" FORCE)

# Download GLFW
FetchContent_Declare(
    glfw
    GIT_REPOSITORY https://github.com/glfw/glfw.git
    GIT_TAG 3.5.1
)

# Download GLM
FetchContent_Declare(
    glm
    GIT_REPOSITORY https://github.com/g-truc/glm.git
    GIT_TAG 1.0.3
)

FetchContent_MakeAvailable(glfw glm)

find_package(OpenGL REQUIRED)

add_executable(physics_simulator
    "${CMAKE_SOURCE_DIR}/src/main.cpp"
    "${CMAKE_SOURCE_DIR}/dependencies/glad/src/gl.c"
)

target_include_directories(physics_simulator PRIVATE
    "${CMAKE_SOURCE_DIR}/include"
    "${CMAKE_SOURCE_DIR}/dependencies/glad/include"
)

target_link_libraries(physics_simulator PRIVATE
    glfw
    glm::glm
    OpenGL::GL
)
