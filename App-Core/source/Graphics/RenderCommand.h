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
            void Clear(float r, float g, float b);
            void DrawArrays(u32 vertexCount);
            void DrawElements(u32 indexCount);
        }
    }
}
