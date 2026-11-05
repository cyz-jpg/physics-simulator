#include "mesh.h"

Mesh::Mesh(const float* vertices, unsigned int vertexCount, glm::vec3 color)
    : Mesh(
        vertices,
        vertexCount,
        std::vector<glm::vec3>(vertexCount, color)
    )
{
}

Mesh::Mesh(
    const float* vertices,
    unsigned int vertexCount,
    const std::vector<glm::vec3>& vertexColors
)
{
    if (vertexColors.size() != vertexCount)
    {
        throw std::invalid_argument(
            "Mesh vertex color count must match vertex count."
        );
    }

    this->vertexCount = vertexCount;

    std::vector<float> vertexData;
    vertexData.reserve(vertexCount * 6);

    for (unsigned int i = 0; i < vertexCount; ++i)
    {
        vertexData.push_back(vertices[i * 3]);
        vertexData.push_back(vertices[i * 3 + 1]);
        vertexData.push_back(vertices[i * 3 + 2]);
        vertexData.push_back(vertexColors[i].r);
        vertexData.push_back(vertexColors[i].g);
        vertexData.push_back(vertexColors[i].b);
    }

    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);

    glBindVertexArray(VAO);

    glBindBuffer(GL_ARRAY_BUFFER, VBO);

    glBufferData(
        GL_ARRAY_BUFFER,
        vertexData.size() * sizeof(float),
        vertexData.data(),
        GL_STATIC_DRAW
    );

    glVertexAttribPointer(
        0,
        3,
        GL_FLOAT,
        GL_FALSE,
        6 * sizeof(float),
        (void*)0
    );

    glEnableVertexAttribArray(0);

    glVertexAttribPointer(
        1,
        3,
        GL_FLOAT,
        GL_FALSE,
        6 * sizeof(float),
        (void*)(3 * sizeof(float))
    );

    glEnableVertexAttribArray(1);

    glBindVertexArray(0);
}

void Mesh::render() const
{
    glBindVertexArray(VAO);

    glDrawArrays(GL_TRIANGLES, 0, vertexCount);

    glBindVertexArray(0);
}

Mesh::~Mesh()
{
    glDeleteVertexArrays(1, &VAO);
    glDeleteBuffers(1, &VBO);
}