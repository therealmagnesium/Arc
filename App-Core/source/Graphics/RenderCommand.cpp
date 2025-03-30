#include "Graphics/RenderCommand.h"

#include <glad/glad.h>
#include <stdlib.h>

namespace Arc
{
    namespace Graphics
    {
        namespace RenderCommand
        {
            void EnableAttribLoc(u32 location)
            {
                glEnableVertexAttribArray(location);
            }

            void DisableAttribLoc(u32 location)
            {
                glDisableVertexAttribArray(location);
            }

            void SetViewport(u32 width, u32 height)
            {
                glViewport(0, 0, width, height);
            }

            void SetPolygonMode(RenderPolygonMode mode)
            {
                switch (mode)
                {
                    case RenderPolygonMode::Fill:
                        glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
                        break;

                    case RenderPolygonMode::Lines:
                        glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
                        break;

                    case RenderPolygonMode::Points:
                        glPolygonMode(GL_FRONT_AND_BACK, GL_POINT);
                        break;
                }
            }

            void Clear(float r, float g, float b)
            {
                glClearColor(r, g, b, 1.f);
                glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
            }

            void DrawArrays(u32 vertexCount)
            {
                glDrawArrays(GL_TRIANGLES, 0, vertexCount);
            }

            void DrawElements(u32 indexCount)
            {
                glDrawElements(GL_TRIANGLES, indexCount, GL_UNSIGNED_INT, NULL);
            }
        }
    }
}
