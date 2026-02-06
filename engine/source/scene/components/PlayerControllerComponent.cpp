#include "scene/components/PlayerControllerComponent.hpp"

#include "scene/GameObject.hpp"
#include "input/InputManager.hpp"
#include "Engine.hpp"

#include <GLFW/glfw3.h>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/vec4.hpp>

namespace eng
{

void PlayerControllerComponent::Init() {
    m_kinematicController = std::make_unique<KinematicCharacterController>(0.4f, 1.2f, m_owner->GetWorldPosition());
}

void PlayerControllerComponent::Update(float deltaTime) {
    auto& inputManager = Engine::GetInstance().GetInputManager();
    auto rotation = m_owner->GetRotation();

    if (inputManager.IsMousePositionChanged()) {
        const auto& oldPos = inputManager.GetMousePositionOld();
        const auto& currentPos = inputManager.GetMousePositionCurrent();
        float deltaX = currentPos.x - oldPos.x;
        float deltaY = currentPos.y - oldPos.y;

        // rot around Y axis
        float yDeltaAngle = -deltaX * m_mouseSensitivity * deltaTime;
        m_yRotation += yDeltaAngle;
        glm::quat yRotation = glm::angleAxis(glm::radians(m_yRotation), glm::vec3(0.f, 1.f, 0.f));
        
        // rot around X axis
        float xDeltaAngle = -deltaY * m_mouseSensitivity * deltaTime;
        m_xRotation += xDeltaAngle;
        m_xRotation = std::clamp(m_xRotation, -89.f, 89.f);
        glm::quat xRotation = glm::angleAxis(glm::radians(m_xRotation), glm::vec3(1.f, 0.f, 0.f));

        rotation = glm::normalize(yRotation * xRotation);

        m_owner->SetRotation(rotation);
    }

    glm::vec3 front = rotation * glm::vec3(0.f, 0.f, -1.f);
    glm::vec3 right = rotation * glm::vec3(1.f, 0.f, 0.f);

    glm::vec3 move(0.f);
    // Left / Right movement
    if (inputManager.IsKeyPressed(GLFW_KEY_A)) {
        move -= right;
    } else if (inputManager.IsKeyPressed(GLFW_KEY_D)) {
        move += right;
    }

    // Up / Down movement
    if (inputManager.IsKeyPressed(GLFW_KEY_W)) {
        move += front;
    } else if (inputManager.IsKeyPressed(GLFW_KEY_S)) {
        move -= front;
    }

    if (inputManager.IsKeyPressed(GLFW_KEY_SPACE)) {
        m_kinematicController->Jump(glm::vec3(0.f, 5.f, 0.f));
    }

    if (glm::dot(move, move) > 0) {
        move = glm::normalize(move);
    }
    
    m_kinematicController->Walk(move * m_moveSpeed * deltaTime);

    m_owner->SetPosition(m_kinematicController->GetPosition());
}

}