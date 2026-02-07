#pragma once

#include <eng.hpp>

class Bullet : public eng::GameObject {
    GAMEOBJECT(Bullet)
public:
    void Update(float deltaTime) override;

private:
    float m_lifetime = 2.f;
};