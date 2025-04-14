#include "ArcEditor.h"

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <imgui.h>

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

static void SetupFramebuffer()
{
    const ApplicationConfig& appInfo = GetApplicationInfo();

    state.framebuffer = CreateFramebuffer(2);
    state.framebuffer.Bind();
    state.framebuffer.attachments[0] = Framebuffer::CreateAttachment(FB_ATTACHMENT_COLOR, 
                                                                     appInfo.windowWidth, 
                                                                     appInfo.windowHeight);

    state.framebuffer.attachments[1] = Framebuffer::CreateAttachment(FB_ATTACHMENT_DEPTH_STENCIL, 
                                                                     appInfo.windowWidth, 
                                                                     appInfo.windowHeight);
    state.framebuffer.Unbind();
    ValidateFramebuffer(state.framebuffer);
}

static void SetupLights()
{
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

void ArcEditor_OnCreate()
{
    const ApplicationConfig& appInfo = GetApplicationInfo();
    SetClearColor(0.07f, 0.07f, 0.07f);

    state.camera.position = glm::vec3(0.f, 0.f, 3.f);
    state.camera.target = glm::vec3(0.f);
    state.camera.up = glm::vec3(0.f, 1.f, 0.f);
    state.camera.moveSpeed = 0.25f;
    state.camera.lookSensitivity = 3.f;
    SetPrimaryCamera(&state.camera);

    SetupFramebuffer();
    LoadFlatColorShader();

    state.cubeMesh = GenMeshCube();
    state.sphereMesh = GenMeshSphere(32, 32, 0.5f);
    state.smallSphereMesh = GenMeshSphere(32, 32, 0.2f);
    state.quadMesh = GenMeshQuad();
    state.model = LoadModel("assets/models/fire_flower.obj");

    SetupLights();

    // state.quadMaterial.albedoTexture = LoadTexture("assets/models/Book.png", TextureFormat::RGBA);
}

void ArcEditor_OnUpdate()
{
    if (IsKeyPressed(KEY_ESCAPE))
        QuitApplication();

    if (IsKeyPressed(KEY_1))
        ModelSetMaterialIndex(state.model, 1);

    if (IsKeyPressed(KEY_2))
        ModelSetMaterialIndex(state.model, 2);

    if (IsKeyPressed(KEY_0))
        ModelSetMaterialIndex(state.model, 0);

    if (IsKeyPressed(KEY_F1))
        RenderCommand::SetPolygonMode(RenderPolygonMode::Points);

    if (IsKeyPressed(KEY_F2))
        RenderCommand::SetPolygonMode(RenderPolygonMode::Lines);

    if (IsKeyPressed(KEY_F3))
        RenderCommand::SetPolygonMode(RenderPolygonMode::Fill);
}

void ArcEditor_OnRender()
{
    state.framebuffer.Bind();
    RendererClear(V3_OPEN(App->clearColor));

    UpdateLightUniforms(state.sun, &Renderer->defaultShader);
    RendererDrawModel(state.model, glm::vec3(0.f));

    for (u32 i = 0; i < LEN(state.lights); i++)
        UpdateLightUniforms(state.lights[i], i, &Renderer->defaultShader);

    RendererDrawMesh(state.cubeMesh, state.material, glm::translate(glm::mat4(1.f), glm::vec3(0.f, 0.f, -3.f)));
    RendererDrawMesh(state.sphereMesh, state.material, glm::translate(glm::mat4(1.f), glm::vec3(5.f, 0.f, 0.f)));
    RendererDrawMesh(state.sphereMesh, state.material, glm::translate(glm::mat4(1.f), glm::vec3(-5.f, 0.f, 0.f)));

    BeginShaderMode(&state.flatColorShader);
    for (u32 i = 0; i < LEN(state.lights); i++)
    {
        Material lightMaterial;
        glm::vec3& position = state.lights[i].position;
        glm::vec3& tint = state.lights[i].color;
        state.flatColorShader.SetVec3("tint", tint);

        RendererDrawMesh(state.smallSphereMesh, lightMaterial, glm::translate(glm::mat4(1.f), position));
    }
    EndShaderMode();

    state.framebuffer.Unbind();
}

void ArcEditor_OnRenderUI()
{
    ImGui::DockSpaceOverViewport();
    ImGui::Begin("Viewport");
    ImGui::Image((ImTextureID)state.framebuffer.attachments[0].id, ImVec2(1600, 900), ImVec2(0,1), ImVec2(1, 0));
    ImGui::End();
}

void ArcEditor_OnShutdown()
{
    DestroyFramebuffer(state.framebuffer);

    UnloadShader(state.flatColorShader);
    // UnloadTexture(state.quadMaterial.albedoTexture);

    UnloadModel(state.model);
    UnloadMesh(state.cubeMesh);
    UnloadMesh(state.quadMesh);
    UnloadMesh(state.sphereMesh);
    UnloadMesh(state.smallSphereMesh);
}
