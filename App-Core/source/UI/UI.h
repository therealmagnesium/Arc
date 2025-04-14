#pragma once
#include <SDL3/SDL_events.h>

namespace Arc
{
    namespace UI    
    {
        void SetupContext();
        void DestroyContext();
        void HandleEvents(void* event);
        void BeginFrome();
        void EndFrame();
        void Display();
    }
}
