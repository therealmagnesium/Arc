#pragma once
#include "Core/Base.h"

#include <SDL3/SDL_video.h>
#include <string>

namespace Arc
{
    namespace Graphics
    {
        struct Window
        {
            u32 width;
            u32 height;
            std::string title;
            void* context = NULL;
            SDL_Window* handle = NULL;
        };

        Window CreateWindow(u32 width, u32 height, const char* title);
        void HandleWindowEvents(Window& window);
        void DisplayWindow(Window& window);
        void DestroyWindow(Window& window);
    }
}
