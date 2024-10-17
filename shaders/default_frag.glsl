#version 430 core
out vec4 FragColor;

in vec2 texCoord;

uniform sampler2D texture0;
uniform sampler2D texture1;

uniform vec3 lightColor;
uniform vec3 objectColor;

void main()
{
    FragColor = vec4(lightColor * objectColor, 1.0);
}
