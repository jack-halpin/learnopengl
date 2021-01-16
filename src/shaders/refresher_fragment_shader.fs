#version 330 core
out vec4 FragColor;
uniform vec4 ourColor;
in vec4 vertexColor;
in vec3 position;

void main()
{
    FragColor = vertexColor;
}