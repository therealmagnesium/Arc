#version 450 core

in vec3 fragPosition;
out vec4 finalColor;

void main()
{
    finalColor = vec4((fragPosition.xyz + vec3(0.5f)) * 1.5f, 1.f);
}
