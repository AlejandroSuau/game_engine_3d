#pragma once

#include "scene/Component.hpp"

#include <glm/mat4x4.hpp>

namespace eng
{

class CameraComponent : public Component {
    COMPONENT(CameraComponent)
public:
    void Update(float deltaTime) override;

    glm::mat4 GetViewMatrix() const;
    glm::mat4 GetProjectionMatrix(float aspectRatio) const;

private:
    float m_fov {60.f}; // field of view
    float m_nearPlane {0.1f};
    float m_farPlane {1000.f};
};

}