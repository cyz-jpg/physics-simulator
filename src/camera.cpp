#include "camera.h"

Camera::Camera(glm::vec3 startPosition, float startTheta, float startPhi)
    : position(startPosition), theta(startTheta), phi(startPhi),dragging(false), lookAtPoint(glm::vec3(0.0f, 0.0f, 0.0f))
{
    forward = glm::vec3(0.0f, 0.0f, -1.0f);
    up = glm::vec3(0.0f, 1.0f, 0.0f);
    right = glm::normalize(glm::cross(forward, up));
}

glm::mat4 Camera::getViewMatrix()
{   
    //always look at the origin
    return glm::lookAt(position, lookAtPoint, up);
}

void Camera::processInput(GLFWwindow* window, float deltaTime)
{
    if (glfwGetKey(window, GLFW_KEY_LEFT_CONTROL) == GLFW_PRESS) {
        if (!ctrlPressed){
            lockMouse = !lockMouse;
            int width, height;
            glfwGetWindowSize(window, &width, &height);
            glfwSetCursorPos(window, width / 2.0, height / 2.0);
            mouseX = width / 2.0;
            mouseY = height / 2.0;
            ctrlPressed = true;
        }
    } else {
        ctrlPressed = false;
    }
    
    if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
        position += forward * deltaTime * 5.0f; // Move forward
        lookAtPoint = position + forward;
    if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
        position -= forward * deltaTime * 5.0f; // Move backward
        lookAtPoint = position + forward;
    if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
        position -= right * deltaTime * 5.0f; // Move left
    if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
        position += right * deltaTime * 5.0f; // Move right
}

void Camera::updateCameraVectors()
{
    const float thetaRadians = glm::radians(theta);
    const float phiRadians = -glm::radians(phi);

    forward.x = cos(thetaRadians) * cos(phiRadians);
    forward.y = sin(phiRadians);
    forward.z = sin(thetaRadians) * cos(phiRadians);

    forward = glm::normalize(forward);

    // Camera vectors
    right = glm::normalize(
        glm::cross(forward, glm::vec3(0, 1, 0))
    );

    up = glm::normalize(
        glm::cross(right, forward)
    );

    lookAtPoint = position + forward;
}

void Camera::mouseButtonCallback(GLFWwindow* window, int button, int action, int mods)
{
    if (button == GLFW_MOUSE_BUTTON_LEFT && !lockMouse) {
        if (action == GLFW_PRESS) {
            dragging = true;
            glfwGetCursorPos(window, &mouseX, &mouseY);
        } else if (action == GLFW_RELEASE) {
            dragging = false;
        }
    }
}

void Camera::mouseMoveCallback(GLFWwindow* window, double xpos, double ypos)
{
    if (dragging || lockMouse) {
        double xoffset = xpos - mouseX;
        double yoffset = mouseY - ypos;

        theta += static_cast<float>(xoffset)*0.2f; // sensitivity
        phi -= static_cast<float>(yoffset)*0.2f; // sensitivity

        updateCameraVectors();

        if (lockMouse) {
            int width, height;
            glfwGetWindowSize(window, &width, &height);
            glfwSetCursorPos(window, width / 2.0, height / 2.0);
            mouseX = width / 2.0;
            mouseY = height / 2.0;
        } else {
            mouseX = xpos;
            mouseY = ypos;
        }
    }
}

void Camera::mouseButtonCallbackStatic(GLFWwindow* window, int button, int action, int mods)
{
    Camera* camera = static_cast<Camera*>(glfwGetWindowUserPointer(window));
    if (camera) {
        camera->mouseButtonCallback(window, button, action, mods);
    }
}

void Camera::mouseMoveCallbackStatic(GLFWwindow* window, double xpos, double ypos)
{
    Camera* camera = static_cast<Camera*>(glfwGetWindowUserPointer(window));
    if (camera) {
        camera->mouseMoveCallback(window, xpos, ypos);
    }
}

void Camera::initMouse(GLFWwindow* window)
{
    glfwSetWindowUserPointer(window, this);
    glfwSetMouseButtonCallback(window, Camera::mouseButtonCallbackStatic);
    glfwSetCursorPosCallback(window, Camera::mouseMoveCallbackStatic);

}

Camera::~Camera()
{
    // CLEANUP IF NEEDED
}