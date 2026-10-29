cmake_minimum_required(VERSION 3.25)
project(PhysicsEngine LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(glfw3 CONFIG REQUIRED)
find_package(glad CONFIG REQUIRED)
find_package(glm CONFIG REQUIRED)
find_package(OpenGL REQUIRED)

add_executable(PhysicsEngine main.cpp)

target_link_libraries(PhysicsEngine PRIVATE
    glfw
    glad::glad
    glm::glm
    OpenGL::GL
)