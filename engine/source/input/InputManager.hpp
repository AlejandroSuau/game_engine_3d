#pragma once

#include <array>

namespace eng
{

class InputManager {
public:

    void SetKeyPressed(int key, bool pressed);
    bool IsKeyPressed(int key);

private:
    friend class Engine;

    std::array<bool, 256> m_keys {false};

    InputManager() = default;
    InputManager(const InputManager&) = delete;
    InputManager(InputManager&&) = delete;
    InputManager& operator=(const InputManager&) = delete;
    InputManager& operator=(InputManager&&) = delete;

    bool IsKeyValid(int key);
};

}