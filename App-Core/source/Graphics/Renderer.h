#pragma once
#include "Graphics/Camera.h"
#include "Graphics/Window.h"

#include <glm/glm.hpp>

namespace Arc
{
    namespace Graphics
    {
        struct RenderState
        {
            Window window;
            glm::mat4 projection = glm::mat4(1.f);
            Camera* primaryCamera = NULL;
        };

        void RendererInit();
        void RendererShutdown();
        void RendererBegin();
        void RendererEnd();
        void RendererClear(float r, float g, float b);

        extern RenderState* Renderer;
    }
}
