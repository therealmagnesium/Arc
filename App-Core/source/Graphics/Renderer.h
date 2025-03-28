#pragma once
#include "Graphics/Camera.h"
#include "Graphics/Material.h"
#include "Graphics/Mesh.h"
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

        void SetPrimaryCamera(Camera* camera);
        void BeginShaderMode(Shader* shader);
        void EndShaderMode();

        extern RenderState* Renderer;
    }
}
