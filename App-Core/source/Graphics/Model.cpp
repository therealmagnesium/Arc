#include "Graphics/Model.h"
#include "Core/Log.h"
#include "Graphics/RenderInternal.h"

#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>

namespace Arc
{
    namespace Graphics
    {
        static const u32 loadFlags = aiProcess_Triangulate | aiProcess_JoinIdenticalVertices;
        static std::vector<Texture> loadedTextures;

        void ProcessNode(Model& model, aiNode* node, const aiScene* scene);
        Mesh ProcessMesh(Model& model, aiMesh* aMesh, const aiScene* scene);

        Model LoadModel(const std::string& path)
        {
            Model model;
            model.path = path;
            model.directory = path.substr(0, path.find_last_of('/')) + "/";

            Assimp::Importer importer;
            const aiScene* scene = importer.ReadFile(path, loadFlags);

            if (!scene || scene->mFlags & AI_SCENE_FLAGS_INCOMPLETE || !scene->mRootNode)
            {
                WARN("Failed to load model %s", path.c_str());
                return model;
            }

            model.meshes.reserve(scene->mNumMeshes);
            model.materials.resize(scene->mNumMaterials);

            ProcessNode(model, scene->mRootNode, scene);

            INFO("Model \"%s\" loaded successfully with %d meshes", path.c_str(), model.meshes.size());
            return model;
        }

        void UnloadModel(Model& model)
        {
            INFO("Unloading model %s...", model.path.c_str());

            for (Mesh& mesh : model.meshes)
                UnloadMesh(mesh);

            for (Material& material : model.materials)
            {
                if (material.albedoTexture.isValid)
                    UnloadTexture(material.albedoTexture);
            }
        }

        void ModelSetMaterialIndex(Model& model, u32 materialIndex)
        {
            for (Mesh& mesh : model.meshes)
                mesh.materialIndex = materialIndex;
        }

        void ProcessNode(Model& model, aiNode* node, const aiScene* scene)
        {
            for (u32 i = 0; i < node->mNumMeshes; i++)
            {
                aiMesh* aMesh = scene->mMeshes[node->mMeshes[i]];
                Mesh mesh = ProcessMesh(model, aMesh, scene);
                model.meshes.push_back(mesh);
            }

            for (u32 i = 0; i < node->mNumChildren; i++)
                ProcessNode(model, node->mChildren[i], scene);
        }

        Mesh ProcessMesh(Model& model, aiMesh* aMesh, const aiScene* scene)
        {
            std::vector<Vertex> vertices;
            std::vector<u32> indices;

            vertices.reserve(aMesh->mNumVertices);

            for (u32 i = 0; i < aMesh->mNumVertices; i++)
            {
                Vertex vertex;
                vertex.position.x = aMesh->mVertices[i].x;
                vertex.position.y = aMesh->mVertices[i].y;
                vertex.position.z = aMesh->mVertices[i].z;

                if (aMesh->HasNormals())
                {
                    vertex.normal.x = aMesh->mNormals[i].x;
                    vertex.normal.y = aMesh->mNormals[i].y;
                    vertex.normal.z = aMesh->mNormals[i].z;
                }

                if (aMesh->HasTextureCoords(0))
                {
                    vertex.uvCoord.x = aMesh->mTextureCoords[0][i].x;
                    vertex.uvCoord.y = aMesh->mTextureCoords[0][i].y;
                }
                else
                    vertex.uvCoord = glm::vec2(0.f);

                vertices.push_back(vertex);
            }

            for (u32 i = 0; i < aMesh->mNumFaces; i++)
            {
                aiFace& face = aMesh->mFaces[i];

                for (u32 j = 0; j < face.mNumIndices; j++)
                    indices.push_back(face.mIndices[j]);
            }

            for (u32 i = 0; i < scene->mNumMaterials; i++)
            {
                Material& material = model.materials[i];
                aiMaterial* aMaterial = scene->mMaterials[i];

                aiColor3D albedo;
                if (aMaterial->Get(AI_MATKEY_COLOR_DIFFUSE, albedo) == AI_SUCCESS)
                {
                    material.albedo.x = albedo.r;
                    material.albedo.y = albedo.g;
                    material.albedo.z = albedo.b;
                }

                bool skipLoading = false;
                aiString aAlbedoTexturePath;
                aMaterial->GetTexture(aiTextureType_DIFFUSE, 0, &aAlbedoTexturePath);

                std::string albedoTexturePath = model.directory + aAlbedoTexturePath.C_Str();

                for (u32 j = 0; j < loadedTextures.size(); j++)
                {
                    if (std::strcmp(loadedTextures[j].path.c_str(), albedoTexturePath.c_str()) == 0)
                    {
                        material.albedoTexture = loadedTextures[j];
                        skipLoading = true;
                        break;
                    }
                }

                if (!skipLoading && albedoTexturePath.size() > model.directory.size() + 3)
                {
                    Texture albedoTexture = LoadTexture(albedoTexturePath.c_str(), TextureFormat::RGBA);
                    material.albedoTexture = albedoTexture;
                    loadedTextures.push_back(albedoTexture);
                }
            }

            Mesh mesh = CreateMesh(vertices.data(), vertices.size(), indices.data(), indices.size());
            mesh.materialIndex = aMesh->mMaterialIndex;
            return mesh;
        }
    }
}
