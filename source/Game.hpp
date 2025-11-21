#pragma once

#include <eng.hpp>

class Game : public eng::Application {
public:
    bool Init() override;
    void Update(float deltaTime) override;
    void Destroy() override;
};