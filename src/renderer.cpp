#include "renderer.h"
#include "shaders.h"
#include "config.h"

Renderer::Renderer()
{
    glEnable(GL_DEPTH_TEST);
    shaderProgram = createShaderProgram("basic.vert", "basic.frag");

    // initialize uniform locations
    viewLoc = glGetUniformLocation(shaderProgram, "view");
    projLoc = glGetUniformLocation(shaderProgram, "projection");
    modelLoc = glGetUniformLocation(shaderProgram, "model");

    // VAO, VBO en EBO aanmaken
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);
    glGenBuffers(1, &EBO);

    // VAO binden
    glBindVertexArray(VAO);

    // VBO en EBO binden
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);

    // VAO unbind
    glBindVertexArray(0);
}

Renderer::~Renderer()
{
    glDeleteVertexArrays(1, &VAO);
    glDeleteBuffers(1, &VBO);
    glDeleteBuffers(1, &EBO);
    glDeleteProgram(shaderProgram);
}

void Renderer::render(Camera& camera)
{
    glUseProgram(shaderProgram);

    glm::mat4 view = camera.getViewMatrix();

    glm::mat4 projection = glm::perspective(
        glm::radians(45.0f),
        (float)SCREEN_WIDTH / (float)SCREEN_HEIGHT,
        0.1f,
        100.0f
    );

    glm::mat4 model = glm::mat4(1.0f);

    glUniformMatrix4fv(viewLoc, 1, GL_FALSE, glm::value_ptr(view));
    glUniformMatrix4fv(projLoc, 1, GL_FALSE, glm::value_ptr(projection));
    glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));

    for (auto& mesh : meshes)
    {
        mesh->render();
    }
}

void Renderer::clear()
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

void Renderer::addMesh(Mesh* mesh)
{
    meshes.push_back(mesh);
}