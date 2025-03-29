#version 450 core

in vec3 fragPosition;
in vec2 fragCoord;
in vec3 fragNormal;
in vec3 worldPosition;

out vec4 finalColor;

struct Attenuation
{
    float constant;
    float linear;
    float quadratic;
};

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

struct PointLight
{
    Attenuation attenuation;
    vec3 position;
    vec3 color;
    float intensity;
};

const int k_maxPointLights = 4;
const float k_ambient = 0.3f;
const vec3 k_v3Zero = vec3(0.f);

uniform Material material;
uniform DirectionalLight sun;
uniform PointLight pointLights[k_maxPointLights];

vec3 GetAlbedoColor()
{
    vec3 texel = texture(material.albedoTexture, fragCoord).xyz;
    vec3 albedo = (all(equal(texel, k_v3Zero))) ? material.albedo : material.albedo * texel;

    return albedo;
}

float CalculateDiffuse(vec3 n, vec3 lightDirection)
{
    float diffuse = max(dot(n, lightDirection), k_ambient);
    return diffuse;
}


vec3 CalculateDirectionalLight(vec3 n)
{
    vec3 lightDirection = normalize(-sun.direction);
    vec3 sunColor = sun.color * sun.intensity;
    vec3 albedo = GetAlbedoColor();
    float diffuse = CalculateDiffuse(n, lightDirection);
    vec3 result = albedo * diffuse * sunColor;

    return max(result, vec3(0.f));
}

vec3 CalculatePointLight(vec3 n, PointLight light)
{
    vec3 lightDirection = normalize(light.position - worldPosition);
    vec3 lightColor = light.color * light.intensity;

    float distance = length(light.position - worldPosition);
    float attenuation = 1.f / (light.attenuation.constant + light.attenuation.linear * distance + light.attenuation.quadratic * pow(distance, 2.f));

    vec3 albedo = GetAlbedoColor();
    float diffuse = CalculateDiffuse(n, lightDirection);

    vec3 result = albedo * diffuse * lightColor * attenuation;
    return max(result, vec3(0.f));
}

void main()
{
    vec3 normal = normalize(fragNormal);
    vec3 result = CalculateDirectionalLight(normal);

    for (int i = 0; i < k_maxPointLights; i++)
        result += CalculatePointLight(normal, pointLights[i]);

    finalColor = vec4(result, 1.f); 
}
