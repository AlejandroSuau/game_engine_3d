#pragma once

#include "scene/Component.hpp"
#include "physics/RigidBody.hpp"

#include <memory>

namespace eng
{

class PhysicsComponent : public Component {
    COMPONENT(PhysicsComponent)
public:
    PhysicsComponent() = default;
    PhysicsComponent(const std::shared_ptr<RigidBody>& body);

    void LoadProperties(const nlohmann::json& json) override;
    void Init() override;
    void Update(float deltaTime) override;

    void SetRigidBody(const std::shared_ptr<RigidBody>& body);

private:
    std::shared_ptr<RigidBody> m_rigidBody;
};

}