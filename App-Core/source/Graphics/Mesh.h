#pragma once
#include "Graphics/RenderInternal.h"
#include "Core/Base.h"

#include <vector>

namespace Arc
{
    namespace Graphics
    {
        struct Mesh
        {
            VertexArray vertexArray;
            VertexBuffer vertexBuffer;
            IndexBuffer indexBuffer;
            std::vector<Vertex> vertices;
            std::vector<u32> indices;
        };

        Mesh CreateMesh(Vertex* vertices, u32 vertexCount, u32* indices, u32 indexCount);
        void UnloadMesh(Mesh& mesh);
        Mesh GenMeshQuad();
        Mesh GenMeshCube();
    }
}
