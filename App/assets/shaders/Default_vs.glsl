#version 450 core
layout (location = 0) in vec3 position;
layout (location = 1) in vec2 uvCoord;

out vec3 fragPosition;
out vec2 fragCoord;

uniform mat4 modelMatrix;
uniform mat4 viewMatrix;
uniform mat4 projectionMatrix;

void main()
{
    fragPosition = position;
    fragCoord = uvCoord;
    gl_Position = projectionMatrix * viewMatrix * modelMatrix * vec4(position, 1.f);
}
