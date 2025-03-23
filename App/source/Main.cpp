#include "ArcEditor.h"

#include <EntryPoint.h>
#include <Arc.h>

using namespace Arc;
using namespace Arc::Core;

void ARC_EntryPoint(Application* app)
{
    app->config.name = "Arc Engine";
    app->config.author = "Magnus Ahlstromer V";
    app->config.windowWidth = 1600;
    app->config.windowHeight = 900;

    app->OnCreate = ArcEditor_OnCreate;
    app->OnUpdate = ArcEditor_OnUpdate;
    app->OnRender = ArcEditor_OnRender;
    app->OnShutdown = ArcEditor_OnShutdown;
}
