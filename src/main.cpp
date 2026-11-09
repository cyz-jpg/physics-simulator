#include "config.h"
#include "shaders.h"
#include "mesh.h"
#include "camera.h"
#include "renderer.h"

std::string loadShader(const char* path);

int main(){
    std::cout << "Starting Physics Simulator..." << std::endl;

    GLFWwindow* window;

    if (!glfwInit()) {
        std::cout << "Failed to initialize GLFW" << std::endl;
        return -1;
    }

    window = glfwCreateWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "Physics Simulator", nullptr, nullptr);

    if(!window) {
        std::cout << "Failed to create GLFW window" << std::endl;
        glfwTerminate();
        return -1;
    }

    glfwMakeContextCurrent(window);

    if (!gladLoadGL(reinterpret_cast<GLADloadfunc>(glfwGetProcAddress))) {
        std::cerr << "Failed to initialize GLAD" << std::endl;
        return -1;
    }

    Camera camera(
        glm::vec3(0.0f, 0.0f, 5.0f), // Start position
        -90.0f,                     // Start theta
        -0.0f                       // Start phi
    );
    camera.initMouse(window);

    // to test
    // Each group of three vertices is one triangle.
    float pyramidVertices[] = {
        // Bottom
        -0.5f, -0.5f, -0.5f,
         0.5f, -0.5f,  0.5f,
         0.5f, -0.5f, -0.5f,
        -0.5f, -0.5f, -0.5f,
        -0.5f, -0.5f,  0.5f,
         0.5f, -0.5f,  0.5f,

        // Sides
        -0.5f, -0.5f, -0.5f,
         0.5f, -0.5f, -0.5f,
         0.0f,  0.5f,  0.0f,
         0.5f, -0.5f, -0.5f,
         0.5f, -0.5f,  0.5f,
         0.0f,  0.5f,  0.0f,
         0.5f, -0.5f,  0.5f,
        -0.5f, -0.5f,  0.5f,
         0.0f,  0.5f,  0.0f,
        -0.5f, -0.5f,  0.5f,
        -0.5f, -0.5f, -0.5f,
         0.0f,  0.5f,  0.0f
    };
    
    std::vector<glm::vec3> pyramidColors = {
        // Bottom
        glm::vec3(0.7f, 0.7f, 0.7f),
        glm::vec3(0.7f, 0.7f, 0.7f),
        glm::vec3(0.7f, 0.7f, 0.7f),
        glm::vec3(0.7f, 0.7f, 0.7f),
        glm::vec3(0.7f, 0.7f, 0.7f),
        glm::vec3(0.7f, 0.7f, 0.7f),

        // Sides
        glm::vec3(1.0f, 0.0f, 0.0f),
        glm::vec3(1.0f, 0.0f, 0.0f),
        glm::vec3(1.0f, 0.0f, 0.0f),
        glm::vec3(0.0f, 1.0f, 0.0f),
        glm::vec3(0.0f, 1.0f, 0.0f),
        glm::vec3(0.0f, 1.0f, 0.0f),
        glm::vec3(0.0f, 0.0f, 1.0f),
        glm::vec3(0.0f, 0.0f, 1.0f),
        glm::vec3(0.0f, 0.0f, 1.0f),
        glm::vec3(1.0f, 1.0f, 0.0f),
        glm::vec3(1.0f, 1.0f, 0.0f),
        glm::vec3(1.0f, 1.0f, 0.0f)
    };

    for (auto &v : pyramidVertices) {
        v += 0.0f;
    }

    Mesh* pyramid = new Mesh(pyramidVertices, 18, pyramidColors);

    Renderer renderer;

    renderer.addMesh(pyramid);

    float deltaTime = 0.0f;
    float lastFrame = 0.0f;

    while (!glfwWindowShouldClose(window))
    {
        // Calculate delta time
        float currentFrame = (float)glfwGetTime();

        deltaTime = currentFrame - lastFrame;
        lastFrame = currentFrame;

        // Clear screen
        glClearColor(0.1f, 0.1f, 0.15f, 1.0f);

        glClear(
            GL_COLOR_BUFFER_BIT |
            GL_DEPTH_BUFFER_BIT
        );

        // Update camera
        camera.processInput(window, deltaTime);

        // Render scene
        renderer.render(camera);

        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    glfwDestroyWindow(window);
    glfwTerminate();

    return 0;
}