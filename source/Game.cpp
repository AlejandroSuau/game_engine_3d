#include "Game.hpp"

#include "TestObject.hpp"

#include <iostream>
#include <string>

bool Game::Init() {
    auto& fs = eng::Engine::GetInstance().GetFileSystem();
    auto texture = eng::Texture::Load("brick.png");

    m_scene = new eng::Scene();
    eng::Engine::GetInstance().SetScene(m_scene);

    auto camera = m_scene->CreateObject("Camera");
    camera->AddComponent(new eng::CameraComponent());
    camera->SetPosition(glm::vec3(0.f, 0.f, 2.f));
    camera->AddComponent(new eng::PlayerControllerComponent());
    m_scene->SetMainCamera(camera);
    m_scene->CreateObject<TestObject>("TestObject");
    
    auto material = eng::Material::Load("materials/brick.mat");

    auto mesh = eng::Mesh::CreateCube();

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

    auto suzanneObj = eng::GameObject::LoadGLTF("models/suzanne/Suzanne.gltf");
    suzanneObj->SetPosition(glm::vec3(0.f, 0.f, -5.f));

    auto gun = eng::GameObject::LoadGLTF("models/sten_gunmachine_carbine/scene.gltf");
    gun->SetParent(camera);
    gun->SetPosition(glm::vec3(0.75f, -0.5f, -0.75));
    gun->SetScale(glm::vec3(-1.f, 1.f, 1.f));

    if (auto anim = gun->GetComponent<eng::AnimationComponent>()) {
        if (auto bullet = gun->FindChildByName("bullet_33")) {
            bullet->SetActive(false);
        }

        if (auto fire = gun->FindChildByName("BOOM_35")) {
            fire->SetActive(false);
        }

        anim->Play("shoot", false);
    }

    auto light = m_scene->CreateObject("Light");
    auto lightComp = new eng::LightComponent();
    lightComp->SetColor(glm::vec4(1.f));
    light->AddComponent(lightComp);
    light->SetPosition(glm::vec3(0.f, 0.5f, 0.f));

    return true;
}

void Game::Update(float deltaTime) {
   m_scene->Update(deltaTime);
}


void Game::Destroy() {

}
