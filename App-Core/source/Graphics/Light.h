#pragma once
#include "Graphics/Shader.h"
#include <glm/glm.hpp>

namespace Arc
{
    namespace Graphics
    {
        enum class LightType
        {
            Directional = 0,
            Point = 1,
            Spot = 2
        };

        struct Light
        {
            LightType type;
            glm::vec3 direction;
            glm::vec3 color;
            float intensity = 0.f;
        };

        Light CreateDirectionalLight(const glm::vec3& direction, const glm::vec3& color, float intensity);
        void UpdateLightUniforms(Light& light, Shader* shader);
    }
}
