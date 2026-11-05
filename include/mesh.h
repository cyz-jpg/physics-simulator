#ifndef MESH_H
#define MESH_H

#include "config.h"

class Mesh
{
private:
    unsigned int VAO = 0;
    unsigned int VBO = 0;
    unsigned int vertexCount = 0;

public:
    Mesh(const float* vertices, unsigned int vertexCount, glm::vec3 color = glm::vec3(1.0f, 1.0f, 1.0f));
    Mesh(
        const float* vertices,
        unsigned int vertexCount,
        const std::vector<glm::vec3>& vertexColors
    );
    ~Mesh();
    void render() const;
};

#endif