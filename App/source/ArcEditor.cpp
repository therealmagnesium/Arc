#include "ArcEditor.h"
#include <glm/glm.hpp>

using namespace Arc;
using namespace Arc::Core;
using namespace Arc::Graphics;

static ArcEditorState state;

void ArcEditor_OnCreate()
{
    state.vao = CreateVertexArray();
    state.vbo = CreateVertexBuffer();
    state.ebo = CreateIndexBuffer();

    state.shader = LoadShader("assets/shaders/Default_vs.glsl", "assets/shaders/Default_fs.glsl");
    state.shader.CreateUniform("tint");

    float vertices[] = {
        -0.5f, 0.5f,  0.f, // v0
        -0.5f, -0.5f, 0.f, // v1
        0.5f,  -0.5f, 0.f, // v2
        0.5f,  0.5f,  0.f  // v3
    };

    u32 indices[] = {
        0, 1, 2, // i0
        2, 3, 0, // i1
    };

    state.vao.Bind();

    state.vbo.Bind();
    state.vbo.SendData(vertices, LEN(vertices));

    state.ebo.Bind();
    state.ebo.SendData(indices, LEN(indices));

    state.vao.SetAttribLoc(0, 3, 0);

    state.vbo.Unbind();
    state.ebo.Unbind();
    state.vao.Unbind();
}

void ArcEditor_OnUpdate()
{
}

void ArcEditor_OnRender()
{
    state.shader.Bind();

    state.shader.SetVec3("tint", glm::vec3(0.2f, 0.6f, 0.8f));

    state.vao.Bind();
    state.ebo.Bind();

    RenderCommand::EnableAttribLoc(0);
    RenderCommand::DrawElements(6);
    RenderCommand::DisableAttribLoc(0);

    state.ebo.Unbind();
    state.vao.Unbind();

    state.shader.Unbind();
}

void ArcEditor_OnShutdown()
{
    UnloadShader(state.shader);
    DestroyVertexBuffer(state.vbo);
    DestroyVertexArray(state.vao);
}
