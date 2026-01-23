#pragma once

#include <array>

#include <glm/vec2.hpp>

namespace eng
{

class InputManager {
public:

    void SetKeyPressed(int key, bool pressed);
    bool IsKeyPressed(int key);

    void SetMouseButtonPressed(int button, bool pressed);
    bool IsMouseButtonPressed(int button);

    void SetMousePositionOld(const glm::vec2& pos);
    const glm::vec2 GetMousePositionOld() const;

    void SetMousePositionCurrent(const glm::vec2& pos);
    const glm::vec2 GetMousePositionCurrent() const;

private:
    friend class Engine;

    std::array<bool, 256> m_keys {false};
    std::array<bool, 16> m_mouseKeys {false};
    glm::vec2 m_mousePositionOld {0.f};
    glm::vec2 m_mousePositionCurrent {0.f};

    InputManager() = default;
    InputManager(const InputManager&) = delete;
    InputManager(InputManager&&) = delete;
    InputManager& operator=(const InputManager&) = delete;
    InputManager& operator=(InputManager&&) = delete;

    bool IsKeyValid(int key);
    bool IsMouseButtonValid(int button);
};

}