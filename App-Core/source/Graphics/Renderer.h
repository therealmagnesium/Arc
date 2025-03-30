#pragma once
#include "Graphics/Camera.h"
#include "Graphics/Material.h"
#include "Graphics/Mesh.h"
#include "Graphics/Model.h"
#include "Graphics/Shader.h"
#include "Graphics/Window.h"

#include <glm/glm.hpp>

namespace Arc
{
    namespace Graphics
    {
        struct RenderState
        {
            Window window;
            Shader defaultShader;
            u32 maxPointLights = 4;
            glm::mat4 projection = glm::mat4(1.f);
            Shader* primaryShader = NULL;
            Camera* primaryCamera = NULL;
        };

        void RendererInit();
        void RendererShutdown();

        void RendererBegin();
        void RendererEnd();

        void RendererClear(float r, float g, float b);
        void RendererDrawMesh(Mesh& mesh, Material& material, const glm::mat4& transform);
        void RendererDrawModel(Model& model, const glm::vec3& position, const glm::vec3& rotation = glm::vec3(0.f),
                               const glm::vec3& scale = glm::vec3(1.f));

        void SetPrimaryCamera(Camera* camera);
        void BeginShaderMode(Shader* shader);
        void EndShaderMode();

        extern RenderState* Renderer;
    }
}
