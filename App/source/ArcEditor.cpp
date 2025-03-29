#include "ArcEditor.h"
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

using namespace Arc;
using namespace Arc::Core;
using namespace Arc::Graphics;

static ArcEditorState state;

static void LoadFlatColorShader()
{
    state.flatColorShader = LoadShader("assets/shaders/FlatColor_vs.glsl", "assets/shaders/FlatColor_fs.glsl");
    state.flatColorShader.CreateUniform("modelMatrix");
    state.flatColorShader.CreateUniform("viewMatrix");
    state.flatColorShader.CreateUniform("projectionMatrix");
    state.flatColorShader.CreateUniform("tint");
}

void ArcEditor_OnCreate()
{
    SetClearColor(0.1f, 0.1f, 0.1f);

    state.camera.position = glm::vec3(0.f, 0.f, 3.f);
    state.camera.target = glm::vec3(0.f);
    state.camera.up = glm::vec3(0.f, 1.f, 0.f);
    state.camera.moveSpeed = 0.25f;
    state.camera.lookSensitivity = 5.f;
    SetPrimaryCamera(&state.camera);

    LoadFlatColorShader();

    state.texture = LoadTexture("assets/textures/texel_checker.png", TextureFormat::RGBA);
    state.material.albedo = glm::vec3(0.7f);
    // state.material.albedoTexture = &state.texture;

    state.cubeMesh = GenMeshCube();
    state.sphereMesh = GenMeshSphere(32, 32, 0.5f);
    state.smallSphereMesh = GenMeshSphere(32, 32, 0.2f);

    state.sun.direction = glm::vec3(0.5f, -1.f, -0.85f);
    state.sun.color = glm::vec3(1.f, 1.f, 0.9f);

    for (u32 i = 0; i < LEN(state.lights); i++)
    {
        PointLight& light = state.lights[i];
        float r = rand() % 256 / 255.f;
        float g = rand() % 256 / 255.f;
        float b = rand() % 256 / 255.f;

        light.intensity = 2.f;
        light.position = glm::vec3(rand() % 10 - 5.f, rand() % 10 - 5.f, rand() % 10 - 5.f);
        light.color = glm::vec3(r, g, b);
        light.attenuation.constant = 1.f;
        light.attenuation.linear = 0.09f;
        light.attenuation.quadratic = 0.032f;
    }
}

void ArcEditor_OnUpdate()
{
    if (IsKeyPressed(KEY_ESCAPE))
        QuitApplication();
}

void ArcEditor_OnRender()
{
    UpdateLightUniforms(state.sun, &Renderer->defaultShader);

    for (u32 i = 0; i < LEN(state.lights); i++)
        UpdateLightUniforms(state.lights[i], i, &Renderer->defaultShader);

    RendererDrawMesh(state.cubeMesh, state.material, glm::translate(glm::mat4(1.f), glm::vec3(0.f)));
    RendererDrawMesh(state.sphereMesh, state.material, glm::translate(glm::mat4(1.f), glm::vec3(2.f, 0.f, 0.f)));
    RendererDrawMesh(state.sphereMesh, state.material, glm::translate(glm::mat4(1.f), glm::vec3(-2.f, 0.f, 0.f)));

    BeginShaderMode(&state.flatColorShader);
    for (u32 i = 0; i < LEN(state.lights); i++)
    {
        glm::vec3& position = state.lights[i].position;
        glm::vec3& tint = state.lights[i].color;
        state.flatColorShader.SetVec3("tint", tint);

        RendererDrawMesh(state.smallSphereMesh, state.material, glm::translate(glm::mat4(1.f), position));
    }
    EndShaderMode();
}

void ArcEditor_OnShutdown()
{
    UnloadShader(state.flatColorShader);
    UnloadTexture(state.texture);

    UnloadMesh(state.cubeMesh);
    UnloadMesh(state.sphereMesh);
    UnloadMesh(state.smallSphereMesh);
}
