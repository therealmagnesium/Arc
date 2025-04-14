#pragma once
#include "Core/Base.h"

#include <glm/glm.hpp>
#include <string>

namespace Arc
{
    namespace Core
    {
        struct ApplicationConfig
        {
            std::string name = "Untitled";
            std::string author = "";
            u32 windowWidth = 1280;
            u32 windowHeight = 720;
        };

        struct Application
        {
            ApplicationConfig config;

            void (*OnCreate)() = NULL;
            void (*OnUpdate)() = NULL;
            void (*OnRender)() = NULL;
            void (*OnRenderUI)() = NULL;
            void (*OnShutdown)() = NULL;
        };

        struct ApplicationState
        {
            bool isRunning = false;
            double lastTime = 0.0;
            glm::vec3 clearColor = glm::vec3(1.f);
            Application* handle = NULL;
        };

        void SetupApplication(Application* app);
        void RunApplication();
        void QuitApplication();

        ApplicationConfig& GetApplicationInfo();
        void SetClearColor(float r, float g, float b);

        extern ApplicationState* App;
    }
}
