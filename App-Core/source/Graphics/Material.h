#pragma once
#include "Graphics/Texture.h"
#include <glm/glm.hpp>

namespace Arc
{
    namespace Graphics
    {
        struct Material
        {
            glm::vec3 albedo = glm::vec3(0.8f);
            Texture* albedoTexture = NULL;
        };

        Material& GetDefaultMaterial();
    }
}
