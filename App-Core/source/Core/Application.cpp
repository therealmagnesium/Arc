#include "Core/Application.h"
#include "Core/Base.h"
#include "Core/Log.h"

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

            state.app->OnCreate();

            isInitialized = true;
        }

        void RunApplication()
        {
            while (state.isRunning)
            {
                state.app->OnUpdate();
                state.app->OnRender();
            }

            state.app->OnShutdown();
        }
    }
}
