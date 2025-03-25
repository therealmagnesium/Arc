#include "Graphics/Renderer.h"
#include "Graphics/RenderCommand.h"
#include "Graphics/Camera.h"
#include "Graphics/Window.h"

#include "Core/Application.h"
#include "Core/Log.h"

#include <SDL3/SDL.h>
#include <glm/gtc/matrix_transform.hpp>

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

            isInitialized = true;
            INFO("%s", "The renderer was successfully initialized");
        }

        void RendererShutdown()
        {
            INFO("%s", "Shutting down the renderer...");

            Graphics::DestroyWindow(state.window);
            SDL_Quit();

            Renderer = NULL;
            state.primaryCamera = NULL;
        }

        void RendererBegin()
        {
            ASSERT(state.primaryCamera != NULL, "The renderer cannot display without a primary camera!");

            UpdateCamera(*state.primaryCamera);

            const Core::ApplicationConfig& config = Core::GetApplicationInfo();
            float aspectRatio = config.windowWidth / (float)config.windowHeight;
            state.projection = glm::perspective(state.primaryCamera->fov, aspectRatio, 0.1f, 300.f);
        }

        void RendererEnd()
        {
            Graphics::DisplayWindow(state.window);
        }

        void RendererClear(float r, float g, float b)
        {
            RenderCommand::Clear(r, g, b);
        }

    }
}
