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
            mesh.vertexArray.SetAttribLoc(2, 3, offsetof(Vertex, normal));

            mesh.indexBuffer.Unbind();
            mesh.vertexBuffer.Unbind();
            mesh.vertexArray.Unbind();
        }
        Mesh CreateMesh(Vertex* vertices, u32 vertexCount)
        {
            Mesh mesh;
            mesh.vertexArray = CreateVertexArray();
            mesh.vertexBuffer = CreateVertexBuffer();

            mesh.vertices.resize(vertexCount);

            for (u32 i = 0; i < vertexCount; i++)
                mesh.vertices[i] = vertices[i];

            PrepareMesh(mesh);

            return mesh;
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
                {glm::vec3(-0.5f, 0.5f, 0.f), glm::vec2(0.f, 1.f), glm::vec3(0.f, 0.f, 1.f)},  // v0
                {glm::vec3(-0.5f, -0.5f, 0.f), glm::vec2(0.f, 0.f), glm::vec3(0.f, 0.f, 1.f)}, // v1
                {glm::vec3(0.5f, -0.5f, 0.f), glm::vec2(1.f, 0.f), glm::vec3(0.f, 0.f, 1.f)},  // v2
                {glm::vec3(0.5f, 0.5f, 0.f), glm::vec2(1.f, 1.f), glm::vec3(0.f, 0.f, 1.f)}    // v3
            };

            u32 indices[6] = {
                0, 1, 2, // i0
                2, 3, 0  // i1
            };

            Mesh mesh = CreateMesh(vertices, LEN(vertices), indices, LEN(indices));
            return mesh;
        }

        Mesh GenMeshCube()
        {
            Vertex vertices[] = {{glm::vec3(-0.5f, -0.5f, -0.5f), glm::vec2(0.f, 0.f), glm::vec3(0.f, 0.f, -1.f)},
                                 {glm::vec3(0.5f, -0.5f, -0.5f), glm::vec2(1.f, 0.f), glm::vec3(0.f, 0.f, -1.f)},
                                 {glm::vec3(0.5f, 0.5f, -0.5f), glm::vec2(1.f, 1.f), glm::vec3(0.f, 0.f, -1.f)},
                                 {glm::vec3(0.5f, 0.5f, -0.5f), glm::vec2(1.f, 1.f), glm::vec3(0.f, 0.f, -1.f)},
                                 {glm::vec3(-0.5f, 0.5f, -0.5f), glm::vec2(0.f, 1.f), glm::vec3(0.f, 0.f, -1.f)},
                                 {glm::vec3(-0.5f, -0.5f, -0.5f), glm::vec2(0.f, 0.f), glm::vec3(0.f, 0.f, -1.f)},

                                 {glm::vec3(-0.5f, -0.5f, 0.5f), glm::vec2(0.f, 0.f), glm::vec3(0.f, 0.f, 1.f)},
                                 {glm::vec3(0.5f, -0.5f, 0.5f), glm::vec2(1.f, 0.f), glm::vec3(0.f, 0.f, 1.f)},
                                 {glm::vec3(0.5f, 0.5f, 0.5f), glm::vec2(1.f, 1.f), glm::vec3(0.f, 0.f, 1.f)},
                                 {glm::vec3(0.5f, 0.5f, 0.5f), glm::vec2(1.f, 1.f), glm::vec3(0.f, 0.f, 1.f)},
                                 {glm::vec3(-0.5f, 0.5f, 0.5f), glm::vec2(0.f, 1.f), glm::vec3(0.f, 0.f, 1.f)},
                                 {glm::vec3(-0.5f, -0.5f, 0.5f), glm::vec2(0.f, 0.f), glm::vec3(0.f, 0.f, 1.f)},

                                 {glm::vec3(-0.5f, 0.5f, 0.5f), glm::vec2(1.f, 0.f), glm::vec3(-1.f, 0.f, 0.f)},
                                 {glm::vec3(-0.5f, 0.5f, -0.5f), glm::vec2(1.f, 1.f), glm::vec3(-1.f, 0.f, 0.f)},
                                 {glm::vec3(-0.5f, -0.5f, -0.5f), glm::vec2(0.f, 1.f), glm::vec3(-1.f, 0.f, 0.f)},
                                 {glm::vec3(-0.5f, -0.5f, -0.5f), glm::vec2(0.f, 1.f), glm::vec3(-1.f, 0.f, 0.f)},
                                 {glm::vec3(-0.5f, -0.5f, 0.5f), glm::vec2(0.f, 0.f), glm::vec3(-1.f, 0.f, 0.f)},
                                 {glm::vec3(-0.5f, 0.5f, 0.5f), glm::vec2(1.f, 0.f), glm::vec3(-1.f, 0.f, 0.f)},

                                 {glm::vec3(0.5f, 0.5f, 0.5f), glm::vec2(1.f, 0.f), glm::vec3(1.f, 0.f, 0.f)},
                                 {glm::vec3(0.5f, 0.5f, -0.5f), glm::vec2(1.f, 1.f), glm::vec3(1.f, 0.f, 0.f)},
                                 {glm::vec3(0.5f, -0.5f, -0.5f), glm::vec2(0.f, 1.f), glm::vec3(1.f, 0.f, 0.f)},
                                 {glm::vec3(0.5f, -0.5f, -0.5f), glm::vec2(0.f, 1.f), glm::vec3(1.f, 0.f, 0.f)},
                                 {glm::vec3(0.5f, -0.5f, 0.5f), glm::vec2(0.f, 0.f), glm::vec3(1.f, 0.f, 0.f)},
                                 {glm::vec3(0.5f, 0.5f, 0.5f), glm::vec2(1.f, 0.f), glm::vec3(1.f, 0.f, 0.f)},

                                 {glm::vec3(-0.5f, -0.5f, -0.5f), glm::vec2(0.f, 1.f), glm::vec3(0.f, -1.f, 0.f)},
                                 {glm::vec3(0.5f, -0.5f, -0.5f), glm::vec2(1.f, 1.f), glm::vec3(0.f, -1.f, 0.f)},
                                 {glm::vec3(0.5f, -0.5f, 0.5f), glm::vec2(1.f, 0.f), glm::vec3(0.f, -1.f, 0.f)},
                                 {glm::vec3(0.5f, -0.5f, 0.5f), glm::vec2(1.f, 0.f), glm::vec3(0.f, -1.f, 0.f)},
                                 {glm::vec3(-0.5f, -0.5f, 0.5f), glm::vec2(0.f, 0.f), glm::vec3(0.f, -1.f, 0.f)},
                                 {glm::vec3(-0.5f, -0.5f, -0.5f), glm::vec2(0.f, 1.f), glm::vec3(0.f, -1.f, 0.f)},

                                 {glm::vec3(-0.5f, 0.5f, -0.5f), glm::vec2(0.f, 1.f), glm::vec3(0.f, 1.f, 0.f)},
                                 {glm::vec3(0.5f, 0.5f, -0.5f), glm::vec2(1.f, 1.f), glm::vec3(0.f, 1.f, 0.f)},
                                 {glm::vec3(0.5f, 0.5f, 0.5f), glm::vec2(1.f, 0.f), glm::vec3(0.f, 1.f, 0.f)},
                                 {glm::vec3(0.5f, 0.5f, 0.5f), glm::vec2(1.f, 0.f), glm::vec3(0.f, 1.f, 0.f)},
                                 {glm::vec3(-0.5f, 0.5f, 0.5f), glm::vec2(0.f, 0.f), glm::vec3(0.f, 1.f, 0.f)},
                                 {glm::vec3(-0.5f, 0.5f, -0.5f), glm::vec2(0.f, 1.), glm::vec3(0.f, 1.f, 0.f)}};

            Mesh mesh = CreateMesh(vertices, LEN(vertices));
            return mesh;
        }

        Mesh GenMeshSphere(u32 stackCount, u32 sectorCount, float radius)
        {
            Mesh mesh;
            mesh.vertexArray = CreateVertexArray();
            mesh.vertexBuffer = CreateVertexBuffer();
            mesh.indexBuffer = CreateIndexBuffer();

            glm::vec3 position;
            glm::vec2 uvCoord;
            glm::vec3 normal;

            float xy;
            float lengthInv = 1.0f / radius; // vertex normal

            float sectorStep = 2 * M_PI / sectorCount;
            float stackStep = M_PI / stackCount;
            float sectorAngle, stackAngle;

            for (int i = 0; i <= stackCount; ++i)
            {
                stackAngle = M_PI / 2 - i * stackStep;  // starting from pi/2 to -pi/2
                xy = radius * cosf(stackAngle);         // r * cos(u)
                position.z = radius * sinf(stackAngle); // r * sin(u)

                // add (sectorCount+1) vertices per stack
                // first and last vertices have same position and normal, but different tex coords
                for (int j = 0; j <= sectorCount; ++j)
                {
                    Vertex vertex;
                    sectorAngle = j * sectorStep; // starting from 0 to 2pi

                    // vertex position (x, y, z)
                    position.x = xy * cosf(sectorAngle); // r * cos(u) * cos(v)
                    position.y = xy * sinf(sectorAngle); // r * cos(u) * sin(v)
                    vertex.position = position;

                    // normalized vertex normal (nx, ny, nz)
                    normal.x = position.x * lengthInv;
                    normal.y = position.y * lengthInv;
                    normal.z = position.z * lengthInv;
                    vertex.normal = normal;

                    // vertex tex coord (s, t) range between [0, 1]
                    uvCoord.x = (float)j / sectorCount;
                    uvCoord.y = (float)i / stackCount;
                    vertex.uvCoord = uvCoord;

                    mesh.vertices.push_back(vertex);
                }
            }

            u32 k1, k2;
            for (int i = 0; i < stackCount; ++i)
            {
                k1 = i * (sectorCount + 1); // beginning of current stack
                k2 = k1 + sectorCount + 1;  // beginning of next stack

                for (int j = 0; j < sectorCount; ++j, ++k1, ++k2)
                {
                    // 2 triangles per sector excluding first and last stacks
                    // k1 => k2 => k1+1
                    if (i != 0)
                    {
                        mesh.indices.push_back(k1);
                        mesh.indices.push_back(k2);
                        mesh.indices.push_back(k1 + 1);
                    }

                    // k1+1 => k2 => k2+1
                    if (i != (stackCount - 1))
                    {
                        mesh.indices.push_back(k1 + 1);
                        mesh.indices.push_back(k2);
                        mesh.indices.push_back(k2 + 1);
                    }
                }
            }

            PrepareMesh(mesh);

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
