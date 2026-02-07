#include "scene/components/PhysicsComponent.hpp"

#include "scene/GameObject.hpp"
#include "Engine.hpp"

namespace eng
{

PhysicsComponent::PhysicsComponent(const std::shared_ptr<RigidBody>& body)
    : m_rigidBody(body) {}

void PhysicsComponent::LoadProperties(const nlohmann::json& json) {
    std::shared_ptr<Collider> collider;
    if (json.contains("collider")) {
        const auto& colliderObj = json["collider"];
        std::string type = colliderObj.value("type", "");
        if (type == "box") {
            const glm::vec3 extents(
                colliderObj.value("x", 1.f),
                colliderObj.value("y", 1.f),
                colliderObj.value("z", 1.f));
            collider = std::make_shared<BoxCollider>(extents);
        } else if (type == "sphere") {
            const float radius = colliderObj.value("r", 1.f);
            collider = std::make_shared<SphereCollider>(radius);
        } else if (type == "capsule") {
            const float radius = colliderObj.value("r", 1.f);
            const float height = colliderObj.value("h", 1.f);
            collider = std::make_shared<CapsuleCollider>(radius, height);
        } else {
            return;
        }

        std::shared_ptr<RigidBody> rigidBody;
        if (json.contains("body")) {
            const auto& bodyObj = json["body"];

            const float mass = bodyObj.value("mass", 0.f);
            const float friction = bodyObj.value("friction", 0.5f);
            std::string typeStr = bodyObj.value("type", "static");

            BodyType type = BodyType::Static;
            if (typeStr == "dynamic") {
                type = BodyType::Dynamic;
            } else if (typeStr == "kinematic") {
                type = BodyType::Kinematic;
            }

            rigidBody = std::make_shared<RigidBody>(type, collider, mass, friction);
        }

        if (rigidBody) {
            SetRigidBody(rigidBody);
        }
    }
}

void PhysicsComponent::Init() {
    if (!m_rigidBody) {
        return;
    }

    const auto pos = m_owner->GetWorldPosition();
    const auto rot = m_owner->GetWorldRotation();

    m_rigidBody->SetPosition(pos);
    m_rigidBody->SetRotation(rot);

    Engine::GetInstance().GetPhysicsManager().AddRigidBody(m_rigidBody.get());
}

void PhysicsComponent::Update(float deltaTime) {
    if (!m_rigidBody) {
        return;
    }

    if (m_rigidBody->GetType() == BodyType::Dynamic) {
        m_owner->SetWorldPosition(m_rigidBody->GetPosition());
        m_owner->SetWorldRotation(m_rigidBody->GetRotation());
    }
}

void PhysicsComponent::SetRigidBody(const std::shared_ptr<RigidBody>& body) {
    m_rigidBody = body;
}

const std::shared_ptr<RigidBody>& PhysicsComponent::GetRigidBody() {
    return m_rigidBody;
}

}