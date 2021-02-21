#version 330 core
out vec4 FragColor;
in vec3 vertexColor;
in vec2 textureCoord;

uniform sampler2D texture1;
uniform sampler2D texture2;

uniform float mixValue;

void main()
{
    vec2 faceCoord = vec2(-textureCoord.x, textureCoord.y);
    FragColor = mix(texture(texture1, textureCoord), texture(texture2, faceCoord), 0.2);
}
