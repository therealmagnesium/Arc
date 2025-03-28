#version 450 core

in vec3 fragPosition;
in vec2 fragCoord;
in vec3 fragNormal;
in vec3 worldPosition;

out vec4 finalColor;

struct Material
{
    vec3 albedo; 
    sampler2D albedoTexture; 
};

struct DirectionalLight
{
    vec3 direction;
    vec3 color;
    float intensity;
};

const float k_ambient = 0.3f;
const vec3 k_v3Zero = vec3(0.f);

uniform Material material;
uniform DirectionalLight sun;

float CalculateDiffuse(vec3 n)
{
    vec3 lightDirection = normalize(-sun.direction);
    float diffuse = max(dot(n, lightDirection), k_ambient);

    return diffuse;
}

vec3 GetAlbedoColor()
{
    vec3 texel = texture(material.albedoTexture, fragCoord).xyz;
    vec3 albedo = (all(equal(texel, k_v3Zero))) ? material.albedo : material.albedo * texel;

    return albedo;
}

void main()
{
    vec3 normal = normalize(fragNormal);
    vec3 albedo = GetAlbedoColor();
    float diffuse = CalculateDiffuse(normal);

    finalColor = vec4(albedo * diffuse * sun.color * sun.intensity, 1.f); 
}
