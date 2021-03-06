#version 330 core
layout (location = 0) in vec3 aPos;
layout (location = 1) in vec3 aColor;
layout (location = 2) in vec2 aTextCoord;

out vec3 vertexColor;
out vec2 textureCoord;
void main()
{
    gl_Position = vec4(aPos.x, aPos.y, aPos.x, 1.0f);
    vertexColor = aColor;
    textureCoord = aTextCoord;
}