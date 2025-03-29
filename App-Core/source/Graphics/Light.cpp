#include "Graphics/Light.h"
#include "Core/Log.h"

namespace Arc
{
    namespace Graphics
    {
        void UpdateLightUniforms(DirectionalLight& light, Shader* shader)
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

            shader->SetVec3("sun.direction", light.direction);
            shader->SetVec3("sun.color", light.color);
            shader->SetFloat("sun.intensity", light.intensity);
        }

        void UpdateLightUniforms(PointLight& light, u32 index, Shader* shader)
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

            shader->SetVec3(("pointLights[" + std::to_string(index) + "].position").c_str(), light.position);
            shader->SetVec3(("pointLights[" + std::to_string(index) + "].color").c_str(), light.color);
            shader->SetFloat(("pointLights[" + std::to_string(index) + "].intensity").c_str(), light.intensity);
            shader->SetFloat(("pointLights[" + std::to_string(index) + "].attenuation.constant").c_str(),
                             light.attenuation.constant);
            shader->SetFloat(("pointLights[" + std::to_string(index) + "].attenuation.linear").c_str(),
                             light.attenuation.linear);
            shader->SetFloat(("pointLights[" + std::to_string(index) + "].attenuation.quadratic").c_str(),
                             light.attenuation.quadratic);
        }
    }

}
