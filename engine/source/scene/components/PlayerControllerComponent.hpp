#pragma once

#include "scene/Component.hpp"
#include "physics/KinematicCharacterController.hpp"

#include <memory>

namespace eng
{

class PlayerControllerComponent : public Component {
    COMPONENT(PlayerControllerComponent);

public:
    void Init() override;
    void Update(float deltaTime) override;
    bool OnGround() const;

private:
    float m_mouseSensitivity {4.5f};
    float m_moveSpeed {30.f};
    float m_xRotation {0.f};
    float m_yRotation {0.f};
    std::unique_ptr<KinematicCharacterController> m_kinematicController;
};

}