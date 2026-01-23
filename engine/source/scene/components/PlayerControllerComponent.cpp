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
        rotation.y -= deltaX * m_mouseSensitivity * deltaTime;
        
        // rot around X axis
        rotation.x -= deltaY * m_mouseSensitivity * deltaTime;

        m_owner->SetRotation(rotation);
    }

    glm::mat4 rotationMatrix(1.f);
    rotationMatrix = glm::rotate(rotationMatrix, rotation.x, glm::vec3(1.f, 0.f, 0.f)); // X-axis
    rotationMatrix = glm::rotate(rotationMatrix, rotation.y, glm::vec3(0.f, 1.f, 0.f)); // Y-axis
    rotationMatrix = glm::rotate(rotationMatrix, rotation.z, glm::vec3(0.f, 0.f, 1.f)); // Z-axis

    glm::vec3 front = glm::normalize(glm::vec3(rotationMatrix * glm::vec4(0.f, 0.f, -1.f, 0.f)));
    glm::vec3 right = glm::normalize(glm::vec3(rotationMatrix * glm::vec4(1.f, 0.f, 0.f, 0.f)));

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