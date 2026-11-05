cmake_minimum_required(VERSION 3.20)

project(physics_simulator VERSION 1.0 LANGUAGES C CXX)

add_executable(physics_simulator
    "${CMAKE_SOURCE_DIR}/src/main.cpp"
    "${CMAKE_SOURCE_DIR}/dependencies/glad/src/gl.c"
)

target_include_directories(physics_simulator PRIVATE
    "${CMAKE_SOURCE_DIR}/include"
    "${CMAKE_SOURCE_DIR}/dependencies/glad/include"
)

find_package(glfw3 3.5 REQUIRED)
find_package(glm CONFIG REQUIRED)

target_link_libraries(physics_simulator PRIVATE
    glfw
    glm::glm
)
