#pragma once
#include "Core/Application.h"
#include "Core/Log.h"

extern void ARC_EntryPoint(Arc::Core::Application* app);

int main(int argc, char** argv)
{
    Arc::Core::Application app;
    ARC_EntryPoint(&app);

    ASSERT(app.OnCreate != NULL && app.OnUpdate != NULL && 
           app.OnRender != NULL && app.OnRenderUI != NULL && 
           app.OnShutdown != NULL, "The application could not find references to it's function pointers!");

    Arc::Core::SetupApplication(&app);
    Arc::Core::RunApplication();
    return 0;
}
