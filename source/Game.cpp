#include "Game.hpp"

#include "TestObject.hpp"
#include "Player.hpp"

#include <iostream>
#include <string>

void Game::RegisterTypes()
{
    Player::Register();
}

bool Game::Init()
{
#if 0
    auto& fs = eng::Engine::GetInstance().GetFileSystem();
    auto texture = eng::Texture::Load("brick.png");

    m_scene = new eng::Scene();
    eng::Engine::GetInstance().SetScene(m_scene);

    auto player = m_scene->CreateObject<Player>("Player");
    player->Init();
    m_scene->SetMainCamera(player);

    m_scene->CreateObject<TestObject>("TestObject");
    
    auto material = eng::Material::Load("materials/brick.mat");

    auto mesh = eng::Mesh::CreateBox();

    auto objectB = m_scene->CreateObject("ObjectB");
    objectB->AddComponent(new eng::MeshComponent(material, mesh));
    objectB->SetPosition(glm::vec3(0.0f, 2.f, 2.f));
    objectB->SetRotation(glm::vec3(0.0f, 2.f, 0.f));

    auto objectC = m_scene->CreateObject("ObjectC");
    objectC->AddComponent(new eng::MeshComponent(material, mesh));
    objectC->SetPosition(glm::vec3(-2.0f, 0.f, 0.f));
    objectC->SetRotation(glm::vec3(0.0f, 0.f, 1.f));
    objectC->SetScale(glm::vec3(1.5f, 1.5f, 1.5f));

    // auto suzanneMesh = eng::Mesh::Load("models/suzanne/suzanne.gltf");
    // auto suzanneMaterial = eng::Material::Load("materials/suzanne.mat");

    // auto suzanneObj = m_scene->CreateObject("Suzanne");
    // suzanneObj->AddComponent(new eng::MeshComponent(suzanneMaterial, suzanneMesh));
    // suzanneObj->SetPosition(glm::vec3(0.f, 0.f, -5.f));

    auto suzanneObj = eng::GameObject::LoadGLTF("models/suzanne/Suzanne.gltf", m_scene);
    suzanneObj->SetPosition(glm::vec3(0.f, 0.f, -5.f));

    

    auto light = m_scene->CreateObject("Light");
    auto lightComp = new eng::LightComponent();
    lightComp->SetColor(glm::vec4(1.f));
    light->AddComponent(lightComp);
    light->SetPosition(glm::vec3(0.f, 0.5f, 0.f));

    auto ground = m_scene->CreateObject("Ground");
    ground->SetPosition(glm::vec3(0, -5.f, 0.f));

    glm::vec3 groundExtents(20.f, 2.f, 20.f);
    auto groundMesh = eng::Mesh::CreateBox(groundExtents);
    ground->AddComponent(new eng::MeshComponent(material, groundMesh));

    auto groundCollider = std::make_shared<eng::BoxCollider>(groundExtents);
    auto groundBody = std::make_shared<eng::RigidBody>(
        eng::BodyType::Static, groundCollider, 0.f, 0.5f);
    ground->AddComponent(new eng::PhysicsComponent(groundBody));

    auto boxObj = m_scene->CreateObject("FallingBox");
    boxObj->AddComponent(new eng::MeshComponent(material, mesh));
    boxObj->SetPosition(glm::vec3(0.f, 2.f, 2.f));
    boxObj->SetRotation(glm::quat(glm::vec3(1.f, 2.f, 0.f)));
    auto boxCollider = std::make_shared<eng::BoxCollider>(glm::vec3(1.f));
    auto boxBody = std::make_shared<eng::RigidBody>(
        eng::BodyType::Dynamic, boxCollider, 5.f, 0.5f
    );
    boxObj->AddComponent(new eng::PhysicsComponent(boxBody));
#endif

    m_scene = eng::Scene::Load("scenes/scene.sc");
    eng::Engine::GetInstance().SetScene(m_scene.get());

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
