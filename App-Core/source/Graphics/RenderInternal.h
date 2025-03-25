#pragma once
#include "Core/Base.h"
#include <glm/glm.hpp>

namespace Arc
{
    namespace Graphics
    {
        struct Vertex
        {
            glm::vec3 position;
            glm::vec2 uvCoord;
        };

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
            void SendData(Vertex* vertices, u32 vertexCount);
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
        void DestroyIndexBuffer(IndexBuffer& vbo);

    }
}
