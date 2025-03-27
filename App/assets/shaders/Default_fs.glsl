#version 450 core

in vec3 fragPosition;
in vec2 fragCoord;
in vec3 fragNormal;

out vec4 finalColor;

const float k_ambient = 0.3f;

vec3 Map(vec3 value, float min1, float max1, float min2, float max2) 
{
    vec3 mappedVec;
    mappedVec.x = min2 + (value.x - min1) * (max2 - min2) / (max1 - min1);
    mappedVec.y = min2 + (value.y - min1) * (max2 - min2) / (max1 - min1);
    mappedVec.z = min2 + (value.z - min1) * (max2 - min2) / (max1 - min1);

    return mappedVec;
}

float CalculateDiffuse(vec3 lightPosition, vec3 n)
{
    vec3 lightDirection = normalize(lightPosition - fragPosition);
    float diffuse = max(dot(n, lightDirection), k_ambient);

    return diffuse;
}

void main()
{
    vec3 normal = normalize(fragNormal);
    float diffuse = CalculateDiffuse(vec3(0.f, 5.f, 4.f), normal);
    finalColor = vec4(vec3(0.8f) * diffuse * vec3(1.f, 1.f, 0.92f), 1.f); 
}
