#include "Graphics/Renderer.h"
#include "Graphics/RenderCommand.h"
#include "Graphics/Camera.h"
#include "Graphics/Window.h"

#include "Core/Application.h"
#include "Core/Log.h"

#include <SDL3/SDL.h>
#include <glm/gtc/matrix_transform.hpp>
#include <glad/glad.h>

namespace Arc
{
    namespace Graphics
    {
        static RenderState state;
        static bool isInitialized = false;
        RenderState* Renderer = NULL;

        void RendererInit()
        {
            if (isInitialized)
            {
                WARN("%s", "Cannot initialize renderer more than once");
                return;
            }

            Renderer = &state;

            const Core::ApplicationConfig& config = Core::GetApplicationInfo();
            bool isSDLLoaded = SDL_Init(SDL_INIT_VIDEO);
            ASSERT(isSDLLoaded, "Failed to initialize SDL3!");

            state.window = Graphics::CreateWindow(config.windowWidth, config.windowHeight, config.name.c_str());
            RenderCommand::SetViewport(config.windowWidth, config.windowHeight);

            state.defaultShader = LoadShader("assets/shaders/Default_vs.glsl", "assets/shaders/Default_fs.glsl");
            state.defaultShader.CreateUniform("modelMatrix");
            state.defaultShader.CreateUniform("viewMatrix");
            state.defaultShader.CreateUniform("projectionMatrix");
            state.defaultShader.CreateUniform("normalMatrix");
            state.primaryShader = &state.defaultShader;

            glEnable(GL_DEPTH_TEST);

            isInitialized = true;
            INFO("%s", "The renderer was successfully initialized");
        }

        void RendererShutdown()
        {
            INFO("%s", "Shutting down the renderer...");

            UnloadShader(state.defaultShader);
            DestroyWindow(state.window);
            SDL_Quit();

            Renderer = NULL;
            state.primaryCamera = NULL;
        }

        void RendererBegin()
        {
            ASSERT(state.primaryCamera != NULL, "The renderer cannot display without a primary camera!");
            ASSERT(state.primaryShader != NULL, "The renderer cannot display without a primary shader!");

            UpdateCamera(*state.primaryCamera);

            const Core::ApplicationConfig& config = Core::GetApplicationInfo();
            float aspectRatio = config.windowWidth / (float)config.windowHeight;
            state.projection = glm::perspective(state.primaryCamera->fov, aspectRatio, 0.1f, 300.f);

            state.defaultShader.Bind();
            state.defaultShader.SetMat4("viewMatrix", state.primaryCamera->view);
            state.defaultShader.SetMat4("projectionMatrix", state.projection);
        }

        void RendererEnd()
        {
            state.defaultShader.Unbind();
            Graphics::DisplayWindow(state.window);
        }

        void RendererClear(float r, float g, float b)
        {
            RenderCommand::Clear(r, g, b);
        }

        void RendererDrawMesh(Mesh& mesh, const glm::mat4& transform)
        {
            const glm::mat4 normalMatrix = glm::transpose(glm::inverse(transform));

            state.primaryShader->SetMat4("modelMatrix", transform);
            state.primaryShader->SetMat4("normalMatrix", normalMatrix);

            if (mesh.indexBuffer.id != 0)
            {
                mesh.vertexArray.Bind();
                mesh.indexBuffer.Bind();

                RenderCommand::EnableAttribLoc(0);
                RenderCommand::EnableAttribLoc(1);
                RenderCommand::EnableAttribLoc(2);

                RenderCommand::DrawElements(mesh.indices.size());

                RenderCommand::DisableAttribLoc(0);
                RenderCommand::DisableAttribLoc(1);
                RenderCommand::DisableAttribLoc(2);

                mesh.indexBuffer.Unbind();
                mesh.vertexArray.Unbind();
            }
            else
            {
                mesh.vertexArray.Bind();

                RenderCommand::EnableAttribLoc(0);
                RenderCommand::EnableAttribLoc(1);
                RenderCommand::EnableAttribLoc(2);

                RenderCommand::DrawArrays(mesh.vertices.size());

                RenderCommand::DisableAttribLoc(0);
                RenderCommand::DisableAttribLoc(1);
                RenderCommand::DisableAttribLoc(2);

                mesh.vertexArray.Unbind();
            }
        }

        void SetPrimaryCamera(Camera* camera)
        {
            state.primaryCamera = camera;
        }

        void BeginShaderMode(Shader* shader)
        {
            state.primaryShader = shader;
            state.primaryShader->Bind();
        }

        void EndShaderMode()
        {
            state.primaryShader->Unbind();
            state.primaryShader = &state.defaultShader;
        }
    }
}
