#include "input/InputManager.hpp"

namespace eng
{
void InputManager::SetKeyPressed(int key, bool pressed) {
    if (!IsKeyValid(key)) return;

    m_keys[key] = pressed;
}

bool InputManager::IsKeyPressed(int key) const {
    return (IsKeyValid(key) && m_keys[key]);
}

bool InputManager::IsKeyValid(int key) const {
    return (key >= 0 && key < static_cast<int>(m_keys.size()));
}

void InputManager::SetMouseButtonPressed(int button, bool pressed) {
    if (!IsMouseButtonValid(button)) return;

    m_mouseKeys[button] = pressed;
}

bool InputManager::IsMouseButtonPressed(int button) const {
    return (IsMouseButtonValid(button) && m_mouseKeys[button]);
}

bool InputManager::IsMouseButtonValid(int button) const {
    return (button >= 0 && button < static_cast<int>(m_mouseKeys.size()));
}

void InputManager::SetMousePositionOld(const glm::vec2& pos) {
    m_mousePositionOld = pos;
}

const glm::vec2 InputManager::GetMousePositionOld() const {
    return m_mousePositionOld;
}

void InputManager::SetMouseButtonWasPressed(int button, bool pressed) {
    if (!IsMouseButtonValid(button)) return;

    m_mouseKeyPressed[button] = pressed;
}

bool InputManager::WasMouseButtonPressed(int button) const {
    return (IsMouseButtonValid(button) && m_mouseKeyPressed[button]);
}

void InputManager::SetMouseButtonWasReleased(int button, bool pressed) {
    if (!IsMouseButtonValid(button)) return;

    m_mouseKeyReleased[button] = pressed;
}

bool InputManager::WasMouseButtonReleased(int button) const {
    return (IsMouseButtonValid(button) && m_mouseKeyReleased[button]);
}

void InputManager::ClearStates() {
    SetMousePositionChanged(false);
    for (auto k : m_mouseKeyPressed) { SetMouseButtonWasPressed(k, false); }
    for (auto k : m_mouseKeyReleased) { SetMouseButtonWasReleased(k, false); }
}

void InputManager::SetMousePositionCurrent(const glm::vec2& pos) {
    m_mousePositionCurrent = pos;
}

const glm::vec2 InputManager::GetMousePositionCurrent() const {
    return m_mousePositionCurrent;
}

void InputManager::SetMousePositionChanged(bool changed) {
    m_mousePositionChanged = changed;
}

bool InputManager::IsMousePositionChanged() const {
    return m_mousePositionChanged;
}

}