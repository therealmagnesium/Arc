#pragma once
#include <Arc.h>

using namespace Arc;
using namespace Arc::Core;
using namespace Arc::Graphics;

struct ArcEditorState
{
    Camera camera;
    Shader flatColorShader;

    Material material;
    Texture texture;

    Mesh cubeMesh;
    Mesh sphereMesh;
    Mesh smallSphereMesh;

    DirectionalLight sun;
    PointLight lights[4];
};

void ArcEditor_OnCreate();
void ArcEditor_OnUpdate();
void ArcEditor_OnRender();
void ArcEditor_OnShutdown();
