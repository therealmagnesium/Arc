#version 450 core

in vec3 fragPosition;
in vec2 fragCoord;
in vec3 fragNormal;
in vec3 worldPosition;

out vec4 finalColor;

uniform vec3 tint;

void main()
{
    finalColor = vec4(tint, 1.f);
}
