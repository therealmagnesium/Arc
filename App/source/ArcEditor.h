#pragma once
#include <Arc.h>

using namespace Arc;
using namespace Arc::Core;
using namespace Arc::Graphics;

struct ArcEditorState
{
    Camera camera;
    Framebuffer framebuffer;
    Shader flatColorShader;

    Material material;
    Material quadMaterial;

    Mesh cubeMesh;
    Mesh sphereMesh;
    Mesh smallSphereMesh;
    Mesh quadMesh;
    Model model;

    DirectionalLight sun;
    PointLight lights[4];
};

void ArcEditor_OnCreate();
void ArcEditor_OnUpdate();
void ArcEditor_OnRender();
void ArcEditor_OnShutdown();
