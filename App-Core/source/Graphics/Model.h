#pragma once
#include "Graphics/Material.h"
#include "Graphics/Mesh.h"

#include "Core/Base.h"

#include <glm/glm.hpp>
#include <vector>

namespace Arc
{
    namespace Graphics
    {
        struct Model
        {
            glm::mat4 transform = glm::mat4(1.f);
            std::vector<Mesh> meshes;
            std::vector<Material> materials;
        };

        Model LoadModel(const char* path);
        void UnloadModel(Model& model);
    }
}
