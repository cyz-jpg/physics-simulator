# Physics Engine

A 3D physics engine built with C++ and OpenGL.

## Features

- OpenGL rendering
- Physics simulation in development

## Technologies

- C++
- OpenGL
- GLFW
- GLAD
- GLM
- CMake
- vcpkg

## Getting Started

### Requirements

- A C++ compiler
- CMake
- Git
- vcpkg

### Build

Clone the repository:

```bash
git clone <repository-url>
cd physics-simulator
```

Install dependencies:

```bash
vcpkg install
```

Configure and build the project:

```bash
cmake -B build -S . -DCMAKE_TOOLCHAIN_FILE="<path-to-vcpkg>/scripts/buildsystems/vcpkg.cmake"
cmake --build build --config Debug
```

## Project Status

Early development.