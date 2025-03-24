#include "Graphics/Window.h"
#include "Core/Application.h"
#include "Core/Log.h"

#include <SDL3/SDL_events.h>
#include <SDL3/SDL_video.h>

namespace Arc
{
    namespace Graphics
    {
        Window CreateWindow(u32 width, u32 height, const char* title)
        {
            Window window;
            window.width = width;
            window.height = height;
            window.title = title;

            SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 4);
            SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 5);
            SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);

            window.handle = SDL_CreateWindow(title, width, height, SDL_WINDOW_OPENGL);
            ASSERT(window.handle != NULL, "Could not create the window!");

            window.context = SDL_GL_CreateContext(window.handle);
            ASSERT(window.context != NULL, "Could not create the window's OpenGL context!");

            SDL_GL_SetSwapInterval(1);

            INFO("Window \"%s\" was successfully created", window.title.c_str());
            return window;
        }

        void HandleWindowEvents(Window& window)
        {
            SDL_Event event;

            while (SDL_PollEvent(&event))
            {
                if (event.type == SDL_EVENT_QUIT)
                    Core::QuitApplication();
            }
        }

        void DisplayWindow(Window& window)
        {
            SDL_GL_SwapWindow(window.handle);
        }

        void DestroyWindow(Window& window)
        {
            INFO("Destroying window \"%s...\"", window.title.c_str());
            SDL_DestroyWindow(window.handle);
        }

    }
}
