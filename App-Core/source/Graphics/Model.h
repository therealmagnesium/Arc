#pragma once
#include "Graphics/Material.h"
#include "Graphics/Mesh.h"
#include "Graphics/Texture.h"

#include <glm/glm.hpp>
#include <string>
#include <vector>

namespace Arc
{
    namespace Graphics
    {
        struct Model
        {
            glm::mat4 transform = glm::mat4(1.f);
            std::string path;
            std::string directory;
            std::vector<Mesh> meshes;
            std::vector<Material> materials;
        };

        Model LoadModel(const std::string& path);
        void UnloadModel(Model& model);
        void ModelSetMaterialIndex(Model& model, u32 materialIndex);
    }
}
