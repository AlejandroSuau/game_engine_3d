#include "input/InputManager.hpp"

namespace eng
{
void InputManager::SetKeyPressed(int key, bool pressed) {
    if (!IsKeyValid(key)) return;

    m_keys[key] = pressed;
}

bool InputManager::IsKeyPressed(int key) {
    return (IsKeyValid(key) && m_keys[key]);
}

bool InputManager::IsKeyValid(int key) {
    return (key >= 0 && key < static_cast<int>(m_keys.size()));
}

void InputManager::SetMouseButtonPressed(int button, bool pressed) {
    if (!IsMouseButtonValid(button)) return;

    m_mouseKeys[button] = pressed;
}


bool InputManager::IsMouseButtonPressed(int button) {
    return (IsMouseButtonValid(button) && m_mouseKeys[button]);
}

bool InputManager::IsMouseButtonValid(int button) {
    return (button >= 0 && button < static_cast<int>(m_mouseKeys.size()));
}

void InputManager::SetMousePositionOld(const glm::vec2& pos) {
    m_mousePositionOld = pos;
}

const glm::vec2 InputManager::GetMousePositionOld() const {
    return m_mousePositionOld;
}

void InputManager::SetMousePositionCurrent(const glm::vec2& pos) {
    m_mousePositionCurrent = pos;
}

const glm::vec2 InputManager::GetMousePositionCurrent() const {
    return m_mousePositionCurrent;
}

}