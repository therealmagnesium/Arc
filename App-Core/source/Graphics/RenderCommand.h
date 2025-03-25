#pragma once
#include "Core/Base.h"

namespace Arc
{
    namespace Graphics
    {
        namespace RenderCommand
        {
            void EnableAttribLoc(u32 location);
            void DisableAttribLoc(u32 location);
            void SetViewport(u32 width, u32 height);
            void Clear(float r, float g, float b);
            void DrawArrays(u32 vertexCount);
            void DrawElements(u32 indexCount);
        }
    }
}
