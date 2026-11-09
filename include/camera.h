#ifndef CAMERA_H
#define CAMERA_H

#include "config.h"

class Camera {

    private:
        glm::vec3 position;
        glm::vec3 forward;
        glm::vec3 up;
        glm::vec3 right;
        glm::vec3 lookAtPoint;
        bool lockMouse = false;
        bool ctrlPressed = false;
        double mouseX;
        double mouseY;
        float theta; // Horizontal angle
        float phi;   // Vertical angle
        void updateCameraVectors();
        bool dragging = false;
        static void mouseButtonCallbackStatic(GLFWwindow* window, int button, int action, int mods);
        static void mouseMoveCallbackStatic(GLFWwindow* window, double xpos, double ypos);
    public:
        void mouseButtonCallback(GLFWwindow* window, int button, int action, int mods);
        void mouseMoveCallback(GLFWwindow* window, double xpos, double ypos);
        void initMouse(GLFWwindow* window);
        Camera(glm::vec3 startPosition = glm::vec3(0.0f, 0.0f, 3.0f), float startTheta = -90.0f, float startPhi = 0.0f);
        void processInput(GLFWwindow* window, float deltaTime);
        glm::mat4 getViewMatrix();
        ~Camera();
    
};

#endif