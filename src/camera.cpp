#include "camera.h"

Camera::Camera(glm::vec3 startPosition, float startTheta, float startPhi, float rotationSpeed, float startRadius)
    : position(startPosition), theta(startTheta), phi(startPhi), rotationspeed(rotationSpeed), radius(startRadius)
{
    forward = glm::vec3(0.0f, 0.0f, -1.0f);
    up = glm::vec3(0.0f, 1.0f, 0.0f);
    right = glm::normalize(glm::cross(forward, up));
}

glm::mat4 Camera::getViewMatrix()
{   
    //always look at the origin
    return glm::lookAt(position, glm::vec3(0.0f,0.0f,0.0f), up);
}

void Camera::processInput(GLFWwindow* window, float deltaTime)
{
    if (glfwGetKey(window, GLFW_KEY_UP) == GLFW_PRESS)    { 
        /* Omhoog */ 
        phi += rotationspeed * deltaTime;
    }
    if (glfwGetKey(window, GLFW_KEY_DOWN) == GLFW_PRESS)  { 
        /* Omlaag */ 
        phi -= rotationspeed * deltaTime;
    }
    if (glfwGetKey(window, GLFW_KEY_LEFT) == GLFW_PRESS)  { 
        /* Links */ 
        theta += rotationspeed * deltaTime;
    }
    if (glfwGetKey(window, GLFW_KEY_RIGHT) == GLFW_PRESS) { 
        /* Rechts */ 
        theta -= rotationspeed * deltaTime;
    }
    updateCameraVectors();
}

void Camera::updateCameraVectors()
{
    // spherical to Cartesian
    const float thetaRadians = glm::radians(theta);
    const float phiRadians = glm::radians(phi);
    const float cosTheta = cos(thetaRadians);
    const float sinTheta = sin(thetaRadians);
    const float cosPhi = cos(phiRadians);
    const float sinPhi = sin(phiRadians);

    position.x = radius * cosTheta * cosPhi;
    position.y = radius * sinPhi;
    position.z = radius * sinTheta * cosPhi;

    // Update forward, right, and up vectors
    forward = glm::normalize(-position); // Look at the origin

    // continuous orientation 
    up = glm::normalize(glm::vec3(
        -cosTheta * sinPhi,
        cosPhi,
        -sinTheta * sinPhi
    ));
    right = glm::normalize(glm::cross(forward, up));
}

Camera::~Camera()
{
    // CLEANUP IF NEEDED
}