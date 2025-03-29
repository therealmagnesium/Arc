#pragma once
#include "Graphics/Shader.h"
#include <glm/glm.hpp>

namespace Arc
{
    namespace Graphics
    {
        struct Attenuation
        {
            float constant = 0.f;
            float linear = 0.f;
            float quadratic = 0.f;
        };

        struct DirectionalLight
        {
            glm::vec3 direction = glm::vec3(0.f, -1.f, 0.f);
            glm::vec3 color = glm::vec3(1.f);
            float intensity = 1.f;
        };

        struct PointLight
        {
            Attenuation attenuation;
            glm::vec3 position = glm::vec3(0.f);
            glm::vec3 color = glm::vec3(1.f);
            float intensity = 1.f;
        };

        void UpdateLightUniforms(DirectionalLight& light, Shader* shader);
        void UpdateLightUniforms(PointLight& light, u32 index, Shader* shader);
    }
}
