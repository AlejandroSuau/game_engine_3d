#include "scene/components/CameraComponent.hpp"

#include "scene/GameObject.hpp"

#include <glm/gtc/matrix_transform.hpp>

namespace eng
{

void CameraComponent::Update(float deltaTime) {

}

glm::mat4 CameraComponent::GetViewMatrix() const {
    return glm::inverse(m_owner->GetWorldTransform());
}

glm::mat4 CameraComponent::GetProjectionMatrix(float aspectRatio) const {
    return glm::perspective(glm::radians(m_fov), aspectRatio, m_nearPlane, m_farPlane);
}

}