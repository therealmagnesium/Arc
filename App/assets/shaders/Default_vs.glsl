#version 450 core
layout (location = 0) in vec3 position;

out vec3 fragPosition;

uniform mat4 viewMatrix;
uniform mat4 projectionMatrix;

void main()
{
    fragPosition = position;
    gl_Position = projectionMatrix * viewMatrix * vec4(position.xyz, 1.f);
}
