#include "scene/components/PlayerControllerComponent.hpp"

#include "scene/GameObject.hpp"
#include "input/InputManager.hpp"
#include "Engine.hpp"

#include <GLFW/glfw3.h>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/vec4.hpp>

namespace eng
{

void PlayerControllerComponent::Update(float deltaTime) {
    auto& inputManager = Engine::GetInstance().GetInputManager();
    auto rotation = m_owner->GetRotation();

    if (inputManager.IsMouseButtonPressed(GLFW_MOUSE_BUTTON_LEFT)) {
        const auto& oldPos = inputManager.GetMousePositionOld();
        const auto& currentPos = inputManager.GetMousePositionCurrent();
        float deltaX = currentPos.x - oldPos.x;
        float deltaY = currentPos.y - oldPos.y;

        // rot around Y axis
        float yAngle = -deltaX * m_mouseSensitivity * deltaTime;
        glm::quat yRotation = glm::angleAxis(yAngle, glm::vec3(0.f, 1.f, 0.f));
        
        // rot around X axis
        float xAngle = -deltaY * m_mouseSensitivity * deltaTime;
        glm::vec3 right = rotation * glm::vec3(1.f, 0.f, 0.f);
        glm::quat xRotation = glm::angleAxis(xAngle, right);

        glm::quat deltaRotation = yRotation * xRotation;
        rotation = glm::normalize(deltaRotation * rotation);

        m_owner->SetRotation(rotation);
    }


    glm::vec3 front = rotation * glm::vec3(0.f, 0.f, -1.f);
    glm::vec3 right = rotation * glm::vec3(1.f, 0.f, 0.f);

    auto position = m_owner->GetPosition();   
    // Left / Right movement
    if (inputManager.IsKeyPressed(GLFW_KEY_A)) {
        position += right * m_moveSpeed * deltaTime;
    } else if (inputManager.IsKeyPressed(GLFW_KEY_D)) {
        position -= right * m_moveSpeed * deltaTime; 
    }

    // Up / Down movement
    if (inputManager.IsKeyPressed(GLFW_KEY_W)) {
        position += front * m_moveSpeed * deltaTime;
    } else if (inputManager.IsKeyPressed(GLFW_KEY_S)) {
        position -= front * m_moveSpeed * deltaTime;
    }

    m_owner->SetPosition(position);
}

}