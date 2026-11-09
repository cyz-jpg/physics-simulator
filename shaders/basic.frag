#version 330 core

out vec4 FragColor;

in vec3 vertexColor;
in mat4 shadow;

void main()
{
    FragColor = vec4(vertexColor, 1.0);
}