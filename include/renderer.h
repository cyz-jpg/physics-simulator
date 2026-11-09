#ifndef RENDERER_H
#define RENDERER_H

#include "camera.h"
#include "mesh.h"

class Renderer {
    private:
        unsigned int shaderProgram = 0;
        unsigned int VAO=0, VBO=0, EBO=0;
        unsigned int viewLoc;
        unsigned int projLoc;
        unsigned int modelLoc;
        unsigned int shaderProgramLoc;
        std::vector<Mesh*> meshes;
    public:
        void addMesh(Mesh* mesh);
        Renderer();
        ~Renderer();
        void render(Camera& camera);
        void clear();
};

#endif