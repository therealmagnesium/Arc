#pragma once
#include "Core/Base.h"

namespace Arc
{
    namespace Graphics
    {
        enum class RenderPolygonMode
        {
            Fill = 0,
            Lines,
            Points,
        };

        namespace RenderCommand
        {
            void EnableAttribLoc(u32 location);
            void DisableAttribLoc(u32 location);
            void SetViewport(u32 width, u32 height);
            void SetPolygonMode(RenderPolygonMode mode);
            void Clear(float r, float g, float b);
            void DrawArrays(u32 vertexCount);
            void DrawElements(u32 indexCount);
        }
    }
}
