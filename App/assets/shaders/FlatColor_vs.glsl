#version 450 core
layout (location = 0) in vec3 position;
layout (location = 1) in vec2 uvCoord;
layout (location = 2) in vec3 normal;

out vec3 fragPosition;
out vec2 fragCoord;
out vec3 worldPosition;

uniform mat4 modelMatrix;
uniform mat4 viewMatrix;
uniform mat4 projectionMatrix;

void main()
{
    fragPosition = position;
    fragCoord = uvCoord;
    worldPosition = position * mat3(modelMatrix);

    gl_Position = projectionMatrix * viewMatrix * modelMatrix * vec4(position, 1.f);
}

