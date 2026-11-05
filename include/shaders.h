#ifndef SHADERS_H
#define SHADERS_H
#include "config.h"

std::string loadShader(const char* path);
unsigned int compileShader(
    unsigned int type,
    const std::string& source);
unsigned int createShaderProgram(char const* vertexPath, char const* fragmentPath);

#endif