#pragma once

#include "scene/Component.hpp"

namespace eng
{

class PlayerControllerComponent : public Component {
    COMPONENT(PlayerControllerComponent);

public:
    void Update(float deltaTime) override;

private:
    float m_mouseSensitivity {0.3f};
    float m_moveSpeed {3.f};

};

}