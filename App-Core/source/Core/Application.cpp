#include "Core/Application.h"
#include "Core/Log.h"

#include "Graphics/Renderer.h"
#include "UI/UI.h"

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
            UI::SetupContext();

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

                UI::BeginFrome();
                state.handle->OnRenderUI();
                UI::EndFrame();

                Graphics::RendererBegin();

                state.handle->OnRender();

                Graphics::RendererClear(V3_OPEN(state.clearColor));
                UI::Display();

                Graphics::RendererEnd();
            }

            state.handle->OnShutdown();
            Graphics::RendererShutdown();
            UI::DestroyContext();
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
