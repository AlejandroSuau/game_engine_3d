#pragma once

#include <eng.hpp>

#include <memory>

class Game : public eng::Application {
public:
    void RegisterTypes() override;
    bool Init() override;
    void Update(float deltaTime) override;
    void Destroy() override;

private:
    eng::Scene* m_scene {nullptr};
};