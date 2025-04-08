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

vec4 GetAlbedoColor()
{
    vec4 texel = texture(material.albedoTexture, fragCoord);
    vec4 albedo = (all(equal(texel.xyz, k_v3Zero))) ? vec4(material.albedo, 1.f) : vec4(material.albedo, 1.f) * texel;

    return albedo;
}

float CalculateDiffuse(vec3 n, vec3 lightDirection)
{
    float diffuse = max(dot(n, lightDirection), k_ambient);
    return diffuse;
}


vec4 CalculateDirectionalLight(vec3 n)
{
    vec3 lightDirection = normalize(-sun.direction);
    vec3 sunColor = sun.color * sun.intensity;
    vec4 albedo = GetAlbedoColor();
    float diffuse = CalculateDiffuse(n, lightDirection);
    vec4 result = albedo * diffuse * vec4(sunColor, 1.f);

    return max(result, vec4(0.f, 0.f, 0.f, 1.f));
}

vec4 CalculatePointLight(vec3 n, PointLight light)
{
    vec3 lightDirection = normalize(light.position - worldPosition);
    vec3 lightColor = light.color * light.intensity;

    float distance = length(light.position - worldPosition);
    float attenuation = 1.f / (light.attenuation.constant + light.attenuation.linear * distance + light.attenuation.quadratic * pow(distance, 2.f));

    vec4 albedo = GetAlbedoColor();
    float diffuse = CalculateDiffuse(n, lightDirection);

    vec4 result = albedo * diffuse * vec4(lightColor, 1.f) * attenuation;
    return max(result, vec4(0.f, 0.f, 0.f, 1.f));
}

void main()
{
    vec3 normal = normalize(fragNormal);
    vec4 result = CalculateDirectionalLight(normal);

    for (int i = 0; i < k_maxPointLights; i++)
        result += CalculatePointLight(normal, pointLights[i]);

    finalColor = result; 
}
