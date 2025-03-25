#version 450 core

in vec3 fragPosition;
out vec4 finalColor;

uniform vec3 tint;

void main()
{
    vec3 color = (fragPosition.xyz + vec3(0.5f)) * 1.5f;
    finalColor = vec4(color, 1.f);
}
