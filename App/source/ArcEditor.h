#pragma once
#include <Arc.h>

using namespace Arc;
using namespace Arc::Core;
using namespace Arc::Graphics;

struct ArcEditorState
{
    Camera camera;
    Mesh mesh;
};

void ArcEditor_OnCreate();
void ArcEditor_OnUpdate();
void ArcEditor_OnRender();
void ArcEditor_OnShutdown();
