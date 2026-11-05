#ifndef CAMERA_H
#define CAMERA_H

#include "config.h"

class Camera {

    private:
        glm::vec3 position;
        glm::vec3 forward;
        glm::vec3 up;
        glm::vec3 right;
        float theta; // Horizontal angle
        float phi;   // Vertical angle
        float rotationspeed;
        float radius;
        void updateCameraVectors();
    public:
        Camera(glm::vec3 startPosition = glm::vec3(0.0f, 0.0f, 3.0f), float startTheta = -90.0f, float startPhi = 0.0f, float rotationSpeed = 90.0f, float startRadius = 3.0f);
        void processInput(GLFWwindow* window, float deltaTime);
        glm::mat4 getViewMatrix();
        ~Camera();
    
};

#endif