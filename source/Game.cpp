#include "Game.hpp"

#include "TestObject.hpp"
#include "Player.hpp"
#include "JumpPlatform.hpp"
#include "Bullet.hpp"

#include <GLFW/glfw3.h>

#include <iostream>
#include <string>

void Game::RegisterTypes()
{
    Player::Register();
    Bullet::Register();
    JumpPlatform::Register();
}

bool Game::Init()
{
    auto& engine = eng::Engine::GetInstance();
    m_scene = eng::Scene::Load("scenes/scene.sc");
    engine.SetScene(m_scene);

    m_3DRoot = m_scene->FindObjectByName("3DRoot");
    if (m_3DRoot) {
        m_3DRoot->SetActive(false);
    }

    auto canvasComponent = engine.GetUIInputSystem().GetCanvas();
    if (!canvasComponent) {
        return false;
    }

    canvasComponent->SetActive(true);
    engine.SetCursorEnabled(true);
    engine.GetUIInputSystem().SetActive(true);

    if (auto button = canvasComponent->GetOwner()->FindChildByName("PlayButton")) {
        if (auto component = button->GetComponent<eng::ButtonComponent>()) {
            component->onClick = [this]() {
                auto& engine = eng::Engine::GetInstance();
                engine.GetUIInputSystem().GetCanvas()->SetActive(false);
                engine.SetCursorEnabled(false);
                if (m_3DRoot) {
                    m_3DRoot->SetActive(true);
                }
            };
        }
    }

    if (auto button = canvasComponent->GetOwner()->FindChildByName("QuitButton")) {
        if (auto component = button->GetComponent<eng::ButtonComponent>()) {
            component->onClick = [this]() {
                SetNeedsToBeClosed(true);
            };
        }
    }

    eng::Engine::GetInstance().GetGraphicsAPI().SetClearColor(
        117.f / 256.f, 187.f / 256.f, 253.f / 256.f, 1.f
    );

    // Example
    /*m_scene = std::make_shared<eng::Scene>();
    engine.SetScene(m_scene.get());

    auto sprite = m_scene->CreateObject("Sprite");
    auto spriteComponent = new eng::SpriteComponent();
    auto texture = eng::Texture::Load("textures/brick.png");
    spriteComponent->SetTexture(texture);
    
    sprite->AddComponent(spriteComponent);
    sprite->SetPosition2D(glm::vec2(500.f, 500.f));
    
    spriteComponent->SetSize(glm::vec2(200.f, 100.f));
    spriteComponent->SetUpperRightUV(glm::vec2(2.f, 1.f));
    sprite->SetRotation2D(glm::radians(45.f));

    auto camera = m_scene->CreateObject("camera");
    auto cameraComponent = new eng::CameraComponent();
    camera->AddComponent(cameraComponent);
    m_scene->SetMainCamera(camera);

    auto canvas = m_scene->CreateObject("Canvas");
    auto canvasComponent = new eng::CanvasComponent();
    canvas->AddComponent(canvasComponent);

    auto& uiInput = engine.GetUIInputSystem();
    uiInput.SetActive(true);
    uiInput.SetCanvas(canvasComponent);

    auto button = m_scene->CreateObject("Button", canvas);
    button->SetPosition2D(glm::vec2(300.f, 300.f));
    auto buttonComponent = new eng::ButtonComponent();
    buttonComponent->SetRect(glm::vec2(150.f, 50.f));
    buttonComponent->SetColor(glm::vec4(0.8f, 0.8f, 0.8f, 1.0f));
    button->AddComponent(buttonComponent);

    auto text = m_scene->CreateObject("Text", canvas);
    text->SetPosition2D(glm::vec2(300.f, 300.f));
    auto textComponent = new eng::TextComponent();
    text->AddComponent(textComponent);
    textComponent->SetText("Some Text");
    textComponent->SetFont("fonts/arial.ttf", 24);
    textComponent->SetColor(glm::vec4(1.f, 0.f, 0.f, 1.f));*/

    return true;
}

void Game::Update(float deltaTime)
{
    if (!m_scene) {
        std::cout << "[INFO] -- No scene available\n";
        return;
    }

    m_scene->Update(deltaTime);

    auto& engine = eng::Engine::GetInstance();
    if (engine.GetInputManager().IsKeyPressed(GLFW_KEY_ESCAPE)) {
        if (m_3DRoot && m_3DRoot->IsActive()) {
            engine.GetUIInputSystem().GetCanvas()->SetActive(true);
            engine.SetCursorEnabled(true);
            m_3DRoot->SetActive(false);
        }
    }

}

void Game::Destroy()
{
}
