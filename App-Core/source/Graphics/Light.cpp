#include "Graphics/Light.h"
#include "Core/Log.h"

namespace Arc
{
    namespace Graphics
    {
        Light CreateDirectionalLight(const glm::vec3& direction, const glm::vec3& color, float intensity)
        {
            Light light;
            light.direction = direction;
            light.color = color;
            light.intensity = intensity;
            light.type = LightType::Directional;

            return light;
        }

        void UpdateLightUniforms(Light& light, Shader* shader)
        {
            static bool hasLoggedError = false;
            if (shader == NULL)
            {
                if (hasLoggedError)
                {
                    ERROR("%s", "Cannot update light uniforms because there is a null shader reference!");
                    hasLoggedError = true;
                }
                return;
            }

            switch (light.type)
            {
                case LightType::Directional:
                    shader->SetVec3("sun.direction", light.direction);
                    shader->SetVec3("sun.color", light.color);
                    shader->SetFloat("sun.intensity", light.intensity);
                    break;

                default:
                    break;
            }
        }

    }
}
