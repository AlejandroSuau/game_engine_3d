#pragma once

#include <eng.hpp>

class Player : public eng::GameObject {
    GAMEOBJECT(Player)
public:
    void Init();
    void Update(float deltaTime) override;

private:
    eng::AnimationComponent* m_animationComponent {nullptr};
};