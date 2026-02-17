#include "Game.hpp"

#include "TestObject.hpp"
#include "Player.hpp"
#include "JumpPlatform.hpp"
#include "Bullet.hpp"

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
    /*m_scene = eng::Scene::Load("scenes/scene.sc");
    eng::Engine::GetInstance().SetScene(m_scene.get());*/

    m_scene = std::make_shared<eng::Scene>();
    eng::Engine::GetInstance().SetScene(m_scene.get());

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

    auto& uiInput = eng::Engine::GetInstance().GetUIInputSystem();
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
    textComponent->SetColor(glm::vec4(1.f, 0.f, 0.f, 1.f));

    return true;
}

void Game::Update(float deltaTime)
{
    if (!m_scene) {
        std::cout << "[INFO] -- No scene available\n";
        return;
    }

    m_scene->Update(deltaTime);
}

void Game::Destroy()
{
}
