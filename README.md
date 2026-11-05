# Physics Simulator

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

## Getting Started

### Requirements

- A C++17-compatible compiler
- CMake 3.20 or newer
- Git
- GLFW 3.5 or newer
- GLM 1.0.3
- GLAD 2.x

GLAD 2 files must be present in the repository at:

```text
dependencies/glad/
```

The expected GLAD layout includes `dependencies/glad/include/glad/gl.h` and
`dependencies/glad/src/gl.c`.

### Build

Clone the repository and configure it:

```bash
git clone <repository-url>
cd physics-simulator
cmake -B build -S .
cmake --build build --config Debug
```

## Project Status

Early development.
