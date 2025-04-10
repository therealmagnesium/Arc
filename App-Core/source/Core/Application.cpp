#include "Core/Application.h"
#include "Core/Log.h"

#include "Graphics/Renderer.h"

#include <glad/glad.h>
#include <SDL3/SDL_init.h>
#include <time.h>

namespace Arc
{
    namespace Core
    {
        static bool isInitialized = false;
        static ApplicationState state;
        ApplicationState* App = NULL;

        void SetupApplication(Application* app)
        {
            if (isInitialized)
            {
                WARN("%s", "Cannot create the application more than once");
                return;
            }

            App = &state;
            srand(time(NULL));

            state.isRunning = true;
            state.handle = app;

            Graphics::RendererInit();

            isInitialized = true;
            INFO("%s", "The application was initialized successfully");
        }

        void RunApplication()
        {
            state.handle->OnCreate();

            while (state.isRunning)
            {
                Graphics::HandleWindowEvents(Graphics::Renderer->window);

                state.handle->OnUpdate();

                Graphics::RendererBegin();

                Graphics::RendererClear(V3_OPEN(state.clearColor));
                state.handle->OnRender();

                Graphics::RendererEnd();
            }

            state.handle->OnShutdown();
            Graphics::RendererShutdown();
        }

        void QuitApplication()
        {
            INFO("%s", "Quitting the application...");
            state.isRunning = false;
        }

        ApplicationConfig& GetApplicationInfo()
        {
            return state.handle->config;
        }

        void SetClearColor(float r, float g, float b)
        {
            state.clearColor = glm::vec3(r, g, b);
        }
    }
}
