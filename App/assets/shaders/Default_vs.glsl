#version 450 core
layout (location = 0) in vec3 position;

out vec3 fragPosition;

void main()
{
    fragPosition = position;
    gl_Position = vec4(position.xyz, 1.f);
}
