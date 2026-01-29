#include "Player.hpp"

#include <GLFW/glfw3.h>

void Player::Init() {
    AddComponent(new eng::CameraComponent());
    SetPosition(glm::vec3(0.f, 0.f, 2.f));
    AddComponent(new eng::PlayerControllerComponent());

    auto gun = eng::GameObject::LoadGLTF("models/sten_gunmachine_carbine/scene.gltf");
    gun->SetParent(this);
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

    m_animationComponent = gun->GetComponent<eng::AnimationComponent>();
}

void Player::Update(float deltaTime) {
    eng::GameObject::Update(deltaTime);

    auto& input = eng::Engine::GetInstance().GetInputManager();
    if (input.IsMouseButtonPressed(GLFW_MOUSE_BUTTON_LEFT)) {
        if (m_animationComponent && !m_animationComponent->IsPlaying()) {
            m_animationComponent->Play("shoot", false);
        }
    }
}