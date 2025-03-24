#pragma once
#include <Arc.h>

using namespace Arc;
using namespace Arc::Core;
using namespace Arc::Graphics;

struct ArcEditorState
{
    VertexArray vao;
    VertexBuffer vbo;
    IndexBuffer ebo;
    Shader shader;
};

void ArcEditor_OnCreate();
void ArcEditor_OnUpdate();
void ArcEditor_OnRender();
void ArcEditor_OnShutdown();
