#version 450 core

in vec3 fragPosition;
in vec2 fragCoord;
out vec4 finalColor;

void main()
{
    vec3 color = fragPosition + vec3(0.5f);
    vec3 uvColor = vec3(fragCoord.xy, 1.f);
    finalColor = vec4(color, 1.f);
}
