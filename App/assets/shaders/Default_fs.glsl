#version 450 core

in vec3 fragPosition;
in vec2 fragCoord;
in vec3 fragNormal;

out vec4 finalColor;

vec3 Map(vec3 value, float min1, float max1, float min2, float max2) 
{
    vec3 mappedVec;
    mappedVec.x = min2 + (value.x - min1) * (max2 - min2) / (max1 - min1);
    mappedVec.y = min2 + (value.y - min1) * (max2 - min2) / (max1 - min1);
    mappedVec.z = min2 + (value.z - min1) * (max2 - min2) / (max1 - min1);

    return mappedVec;
}

void main()
{
    vec3 color = mix(fragPosition + vec3(0.5f), vec3(0.f, 0.87f, 0.92f), 0.4f);
    vec3 uvColor = vec3(fragCoord.xy, 1.f);
    vec3 normalColor = Map(fragNormal, -1.f, 1.f, 0.5f, 1.f);
    finalColor = vec4(color, 1.f); 
}
