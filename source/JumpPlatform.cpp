#include "JumpPlatform.hpp"

void JumpPlatform::Init() {
    auto physics = GetComponent<eng::PhysicsComponent>();
    if (!physics) { return; }

    auto rigidBody = physics->GetRigidBody();
    if (!rigidBody) { return; }

    rigidBody->AddContactListener(this);
}

void JumpPlatform::OnContact(
    eng::CollisionObject* obj,
    const glm::vec3& pos,
    const glm::vec3& norm) {
    
    if (obj->GetCollisionObjectType() == eng::CollisionObjectType::KinematicCharacterController) {
        auto controller = static_cast<eng::KinematicCharacterController*>(obj);
        if (controller) {
            controller->Jump(glm::vec3(0.f, 20.f, 0.f));
        }
    }

}
