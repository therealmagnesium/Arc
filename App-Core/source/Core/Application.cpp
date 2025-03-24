#include "Core/Application.h"
#include "Core/Base.h"
#include "Core/Log.h"

#include "Graphics/RenderCommand.h"

#include <glad/glad.h>
#include <SDL3/SDL_init.h>

namespace Arc
{
    namespace Core
    {
        static bool isInitialized = false;
        static ApplicationState state;

        void SetupApplication(Application* app)
        {
            if (isInitialized)
            {
                WARN("Cannot create the application more than once");
                return;
            }

            state.isRunning = true;
            state.app = app;

            bool isSDLLoaded = SDL_Init(SDL_INIT_VIDEO);
            ASSERT(isSDLLoaded, "Failed to initialize SDL3!");

            state.window =
                Graphics::CreateWindow(app->config.windowWidth, app->config.windowHeight, app->config.name.c_str());

            state.app->OnCreate();

            isInitialized = true;
            INFO("Successfully created the application");
        }

        void RunApplication()
        {
            while (state.isRunning)
            {
                Graphics::HandleWindowEvents(state.window);

                state.app->OnUpdate();

                Graphics::RenderCommand::Clear(0.1f, 0.1f, 0.1f);
                state.app->OnRender();

                Graphics::DisplayWindow(state.window);
            }

            state.app->OnShutdown();
            Graphics::DestroyWindow(state.window);
            SDL_Quit();
        }

        void QuitApplication()
        {
            INFO("Quitting the application...");
            state.isRunning = false;
        }
    }
}
