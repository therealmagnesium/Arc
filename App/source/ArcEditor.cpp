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
    state.camera.moveSpeed = 0.25f;
    state.camera.lookSensitivity = 5.f;
    SetPrimaryCamera(&state.camera);

    state.texture = LoadTexture("assets/textures/small_checker.png", TextureFormat::RGB);
    state.material.albedo = glm::vec3(0.8f, 0.6f, 0.3f);
    // state.material.albedoTexture = &state.texture;

    state.cubeMesh = GenMeshCube();
    state.sphereMesh = GenMeshSphere(32, 32, 0.5f);

    state.sun = CreateDirectionalLight(glm::vec3(0.5f, -1.f, -0.85f), glm::vec3(1.f, 1.f, 0.9f), 1.f);
}

void ArcEditor_OnUpdate()
{
    if (IsKeyPressed(KEY_ESCAPE))
        QuitApplication();
}

void ArcEditor_OnRender()
{
    UpdateLightUniforms(state.sun, &Renderer->defaultShader);

    RendererDrawMesh(state.cubeMesh, state.material, glm::mat4(1.f));
    RendererDrawMesh(state.sphereMesh, state.material, glm::translate(glm::mat4(1.f), glm::vec3(2.f, 0.f, 0.f)));
    RendererDrawMesh(state.sphereMesh, state.material, glm::translate(glm::mat4(1.f), glm::vec3(-2.f, 0.f, 0.f)));
}

void ArcEditor_OnShutdown()
{
    UnloadTexture(state.texture);
    UnloadMesh(state.cubeMesh);
    UnloadMesh(state.sphereMesh);
}
