#include "UI/UI.h"
#include "Graphics/Renderer.h"
#include "Core/Log.h"

#include <SDL3/SDL_events.h>
#include <imgui.h>
#include <imgui_impl_sdl3.h>
#include <imgui_impl_opengl3.h>

namespace Arc
{
    namespace UI
    {
        void SetupContext()
        {
            ASSERT(Graphics::Renderer != NULL, "%s", "Cannot initialize the UI context when the renderer hasn't been intialized!");

            IMGUI_CHECKVERSION();
            ImGui::CreateContext();
            ImGuiIO& io = ImGui::GetIO();
            (void)io;
            io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard; // Enable Keyboard Controls
            io.ConfigFlags |= ImGuiConfigFlags_NavEnableGamepad;  // Enable Gamepad Controls
            io.ConfigFlags |= ImGuiConfigFlags_DockingEnable;

            // Setup Dear ImGui style
            ImGui::StyleColorsDark();
            // ImGui::StyleColorsLight();

            // Setup Platform/Renderer backends
            ImGui_ImplSDL3_InitForOpenGL(Graphics::Renderer->window.handle, Graphics::Renderer->window.context);
            ImGui_ImplOpenGL3_Init("#version 450");

            INFO("The UI context was setup successfully");
        }

        void DestroyContext()
        {
            INFO("Destroying the UI context...");

            ImGui_ImplOpenGL3_Shutdown();
            ImGui_ImplSDL3_Shutdown();
            ImGui::DestroyContext();
        }

        void HandleEvents(void* event)
        {
            ImGui_ImplSDL3_ProcessEvent((SDL_Event*)event);
        }

        void BeginFrome()
        {
            ImGui_ImplOpenGL3_NewFrame();
            ImGui_ImplSDL3_NewFrame();
            ImGui::NewFrame();
        }

        void EndFrame()
        {
            ImGui::Render();
        }

        void Display()
        {
            ImDrawData* drawData = ImGui::GetDrawData();
            ASSERT(drawData != NULL, "%s", "The UI crashed because there is no draw data!");
            ImGui_ImplOpenGL3_RenderDrawData(drawData);
        }
    }
}
