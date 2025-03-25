#include "Graphics/Mesh.h"
#include "Graphics/RenderInternal.h"

#include "Core/Base.h"

namespace Arc
{
    namespace Graphics
    {
        static void PrepareMesh(Mesh& mesh)
        {
            mesh.vertexArray.Bind();

            mesh.vertexBuffer.Bind();
            mesh.vertexBuffer.SendData(mesh.vertices.data(), mesh.vertices.size());

            mesh.indexBuffer.Bind();
            mesh.indexBuffer.SendData(mesh.indices.data(), mesh.indices.size());

            mesh.vertexArray.SetAttribLoc(0, 3, offsetof(Vertex, position));
            mesh.vertexArray.SetAttribLoc(1, 2, offsetof(Vertex, uvCoord));

            mesh.indexBuffer.Unbind();
            mesh.vertexBuffer.Unbind();
            mesh.vertexArray.Unbind();
        }

        Mesh CreateMesh(Vertex* vertices, u32 vertexCount, u32* indices, u32 indexCount)
        {
            Mesh mesh;
            mesh.vertexArray = CreateVertexArray();
            mesh.vertexBuffer = CreateVertexBuffer();
            mesh.indexBuffer = CreateIndexBuffer();

            mesh.vertices.resize(vertexCount);
            mesh.indices.resize(indexCount);

            for (u32 i = 0; i < vertexCount; i++)
                mesh.vertices[i] = vertices[i];

            for (u32 i = 0; i < indexCount; i++)
                mesh.indices[i] = indices[i];

            PrepareMesh(mesh);

            return mesh;
        }

        Mesh GenMeshQuad()
        {
            Vertex vertices[4] = {
                {glm::vec3(-0.5f, 0.5f, 0.f), glm::vec2(0.f, 1.f)},  // v0
                {glm::vec3(-0.5f, -0.5f, 0.f), glm::vec2(0.f, 0.f)}, // v1
                {glm::vec3(0.5f, -0.5f, 0.f), glm::vec2(1.f, 0.f)},  // v2
                {glm::vec3(0.5f, 0.5f, 0.f), glm::vec2(1.f, 1.f)}    // v3
            };

            u32 indices[6] = {
                0, 1, 2, // i0
                2, 3, 0  // i1
            };

            Mesh mesh = CreateMesh(vertices, LEN(vertices), indices, LEN(indices));
            return mesh;
        }

        void UnloadMesh(Mesh& mesh)
        {
            DestroyIndexBuffer(mesh.indexBuffer);
            DestroyVertexBuffer(mesh.vertexBuffer);
            DestroyVertexArray(mesh.vertexArray);
        }

    }
}
