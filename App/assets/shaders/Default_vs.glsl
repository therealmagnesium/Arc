#version 450 core
layout (location = 0) in vec3 position;
layout (location = 1) in vec2 uvCoord;

out vec3 fragPosition;
out vec2 fragCoord;

uniform mat4 viewMatrix;
uniform mat4 projectionMatrix;

void main()
{
    fragPosition = position;
    fragCoord = uvCoord;
    gl_Position = projectionMatrix * viewMatrix * vec4(position.xyz, 1.f);
}
