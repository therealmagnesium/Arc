#include "Graphics/RenderInternal.h"
#include "Core/Log.h"

#include <glad/glad.h>

namespace Arc
{
    namespace Graphics
    {
        VertexArray CreateVertexArray()
        {
            VertexArray vao;
            glGenVertexArrays(1, &vao.id);

            return vao;
        }

        void DestroyVertexArray(VertexArray& vao)
        {
            vao.Unbind();
            glDeleteVertexArrays(1, &vao.id);
        }

        VertexBuffer CreateVertexBuffer()
        {
            VertexBuffer vbo;
            glGenBuffers(1, &vbo.id);

            return vbo;
        }

        void DestroyVertexBuffer(VertexBuffer& vbo)
        {
            vbo.Unbind();
            glDeleteBuffers(1, &vbo.id);
        }

        IndexBuffer CreateIndexBuffer()
        {
            IndexBuffer ebo;
            glGenBuffers(1, &ebo.id);

            return ebo;
        }

        void DestroyIndexBuffer(IndexBuffer& ebo)
        {
            ebo.Unbind();
            glDeleteBuffers(1, &ebo.id);
        }

        void VertexArray::Bind()
        {
            glBindVertexArray(id);
            isSelected = true;
        }

        void VertexArray::Unbind()
        {
            glBindVertexArray(0);
            isSelected = false;
        }

        void VertexArray::SetAttribLoc(u32 location, u32 elementCount, u32 offset)
        {
            if (isSelected)
                glVertexAttribPointer(location, elementCount, GL_FLOAT, false, 3 * sizeof(float), (void*)(u64)offset);
        }

        void VertexBuffer::Bind()
        {
            glBindBuffer(GL_ARRAY_BUFFER, id);
            isSelected = true;
        }

        void VertexBuffer::Unbind()
        {
            glBindBuffer(GL_ARRAY_BUFFER, 0);
            isSelected = false;
        }

        void VertexBuffer::SendData(float* vertices, u32 vertexCount)
        {
            if (isSelected)
                glBufferData(GL_ARRAY_BUFFER, vertexCount * sizeof(float), vertices, GL_STATIC_DRAW);
        }

        void IndexBuffer::Bind()
        {
            glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, id);
            isSelected = true;
        }

        void IndexBuffer::Unbind()
        {
            glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
            isSelected = false;
        }

        void IndexBuffer::SendData(u32* indices, u32 indexCount)
        {
            if (isSelected)
                glBufferData(GL_ELEMENT_ARRAY_BUFFER, indexCount * sizeof(u32), indices, GL_STATIC_DRAW);
        }
    }
}
