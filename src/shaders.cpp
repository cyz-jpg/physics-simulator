
#include "config.h"
#include "shaders.h"

// ============================================
// LOAD SHADER FROM FILE
// ============================================

std::string loadShader(const char* filename)
{
    std::filesystem::path shaderPath =
        std::filesystem::path(PHYSICS_SIMULATOR_PROJECT_ROOT)
        / "shaders"
        / filename;

    std::ifstream file(shaderPath);

    if (!file.is_open())
    {
        std::cerr << "[Shader Error] Cannot open file: "
                  << shaderPath.string() << std::endl;

        return "";
    }

    std::stringstream buffer;
    buffer << file.rdbuf();

    if (file.bad())
    {
        std::cerr << "[Shader Error] Failed reading file: "
                  << shaderPath.string() << std::endl;

        return "";
    }

    return buffer.str();
}

// ============================================
// COMPILE SHADER
// ============================================

unsigned int compileShader(
    unsigned int type,
    const std::string& source)
{
    unsigned int shader = glCreateShader(type);

    if (shader == 0)
    {
        std::cerr << "[Shader Error] Failed to create shader."
                  << std::endl;

        return 0;
    }

    const char* src = source.c_str();

    glShaderSource(shader, 1, &src, nullptr);
    glCompileShader(shader);

    int success = 0;

    glGetShaderiv(
        shader,
        GL_COMPILE_STATUS,
        &success
    );

    if (!success)
    {
        char infoLog[1024];

        glGetShaderInfoLog(
            shader,
            sizeof(infoLog),
            nullptr,
            infoLog
        );

        std::cerr << "[Shader Compile Error]\n"
                  << infoLog << std::endl;

        glDeleteShader(shader);

        return 0;
    }

    return shader;
}

// ============================================
// CREATE SHADER PROGRAM
// ============================================

unsigned int createShaderProgram(char const* vertexPath, char const* fragmentPath)
{
    // Load shader files
    std::string vertexCode =
        loadShader(vertexPath);

    std::string fragmentCode =
        loadShader(fragmentPath);

    if (vertexCode.empty() || fragmentCode.empty())
    {
        std::cerr << "[Shader Error] Failed to load shader files."
                  << std::endl;

        return 0;
    }

    // Compile vertex shader
    unsigned int vertexShader =
        compileShader(GL_VERTEX_SHADER, vertexCode);

    if (vertexShader == 0)
        return 0;

    // Compile fragment shader
    unsigned int fragmentShader =
        compileShader(GL_FRAGMENT_SHADER, fragmentCode);

    if (fragmentShader == 0)
    {
        glDeleteShader(vertexShader);
        return 0;
    }

    // Create shader program
    unsigned int program = glCreateProgram();

    if (program == 0)
    {
        std::cerr << "[Shader Error] Failed to create program."
                  << std::endl;

        glDeleteShader(vertexShader);
        glDeleteShader(fragmentShader);

        return 0;
    }

    // Attach shaders
    glAttachShader(program, vertexShader);
    glAttachShader(program, fragmentShader);

    // Link program
    glLinkProgram(program);

    // Check linking status
    int success = 0;

    glGetProgramiv(
        program,
        GL_LINK_STATUS,
        &success
    );

    if (!success)
    {
        char infoLog[1024];

        glGetProgramInfoLog(
            program,
            sizeof(infoLog),
            nullptr,
            infoLog
        );

        std::cerr << "[Shader Link Error]\n"
                  << infoLog << std::endl;

        glDeleteProgram(program);
        program = 0;
    }

    // Delete shader objects
    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader);

    return program;
}
