#pragma once
#include <Arc.h>
#include <glm/glm.hpp>

using namespace Arc;
using namespace Arc::Core;
using namespace Arc::Graphics;

struct ArcEditorState
{
    glm::mat4 projection = glm::mat4(1.f);

    Camera camera;
    VertexArray vao;
    VertexBuffer vbo;
    IndexBuffer ebo;
    Shader shader;
};

void ArcEditor_OnCreate();
void ArcEditor_OnUpdate();
void ArcEditor_OnRender();
void ArcEditor_OnShutdown();
