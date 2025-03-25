#include "ArcEditor.h"
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

using namespace Arc;
using namespace Arc::Core;
using namespace Arc::Graphics;

static ArcEditorState state;

void ArcEditor_OnCreate()
{
    SetClearColor(0.1f, 0.1f, 0.1f);

    state.camera.position = glm::vec3(0.f, 0.f, 3.f);
    state.camera.target = glm::vec3(0.f);
    state.camera.up = glm::vec3(0.f, 1.f, 0.f);
    state.camera.moveSpeed = 0.1f;
    state.camera.lookSensitivity = 5.f;
    SetPrimaryCamera(&state.camera);

    state.mesh = GenMeshCube();
}

void ArcEditor_OnUpdate()
{
    if (IsKeyPressed(KEY_ESCAPE))
        QuitApplication();
}

void ArcEditor_OnRender()
{
    RendererDrawMesh(state.mesh);
}

void ArcEditor_OnShutdown()
{
    UnloadMesh(state.mesh);
}
