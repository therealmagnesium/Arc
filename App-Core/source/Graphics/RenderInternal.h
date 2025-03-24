#pragma once
#include "Core/Base.h"

namespace Arc
{
    namespace Graphics
    {
        struct VertexArray
        {
            u32 id = 0;
            bool isSelected = false;

            void Bind();
            void Unbind();
            void SetAttribLoc(u32 location, u32 elementCount, u32 offset);
        };

        struct VertexBuffer
        {
            u32 id = 0;
            bool isSelected = false;

            void Bind();
            void Unbind();
            void SendData(float* vertices, u32 vertexCount);
        };

        struct IndexBuffer
        {
            u32 id = 0;
            bool isSelected = false;

            void Bind();
            void Unbind();
            void SendData(u32* indices, u32 indexCount);
        };

        VertexArray CreateVertexArray();
        VertexBuffer CreateVertexBuffer();
        IndexBuffer CreateIndexBuffer();
        void DestroyVertexArray(VertexArray& vao);
        void DestroyVertexBuffer(VertexBuffer& vbo);
        void DestroyIndexBuffer(VertexBuffer& vbo);

    }
}
