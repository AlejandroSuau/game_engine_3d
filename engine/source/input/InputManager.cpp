#include "input/InputManager.hpp"

namespace eng
{
void InputManager::SetKeyPressed(int key, bool pressed) {
    if (!IsKeyValid(key)) return;

    m_keys[key] = pressed;
}

bool InputManager::IsKeyPressed(int key) {
    if (!IsKeyValid(key)) return false;

    return m_keys[key];
}

bool InputManager::IsKeyValid(int key) {
    return (key >= 0 || key < static_cast<int>(m_keys.size()));
}

}