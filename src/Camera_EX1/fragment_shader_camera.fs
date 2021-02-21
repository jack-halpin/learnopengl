#version 330 core
out vec4 FragColor;
uniform vec4 ourColor;

in vec2 textureCoord;
in vec4 vertexColor;

uniform sampler2D texture1;
uniform sampler2D texture2;

uniform float mixValue;

void main()
{
	vec2 faceCoord = textureCoord;
	faceCoord.x = -faceCoord.x;
	vec2 containerCoord = textureCoord;
    FragColor = mix(texture(texture1, containerCoord), texture(texture2, faceCoord), mixValue);
}
