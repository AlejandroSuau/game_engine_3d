#pragma once

#include "scene/Component.hpp"

#include <glm/vec4.hpp>
#include <glm/vec2.hpp>
#include <memory>

namespace eng
{

class Texture;

class SpriteComponent : public Component {
    COMPONENT(SpriteComponent)
public:
    void LoadProperties(const nlohmann::json& json) override;
    void Update(float deltaTime) override;

    [[nodiscard]] const std::shared_ptr<Texture>& GetTexture() const noexcept;
    void SetTexture(const std::shared_ptr<Texture>& texture) noexcept;
    [[nodiscard]] const glm::vec4& GetColor() const noexcept;
    void SetColor(const glm::vec4& color) noexcept;
    [[nodiscard]] const glm::vec2& GetSize() const noexcept;
    void SetSize(const glm::vec2& size) noexcept;
    [[nodiscard]] const glm::vec2& GetLowerLeftUV() const noexcept;
    void SetUV(const glm::vec2& lowerLeftUV, const glm::vec2& upperRightUV) noexcept;
    void SetLowerLeftUV(const glm::vec2& uv) noexcept;
    [[nodiscard]] const glm::vec2& GetUpperRightUV() const noexcept;
    void SetUpperRightUV(const glm::vec2& uv) noexcept;
    [[nodiscard]] const glm::vec2& GetPivot() const noexcept;
    void SetPivot(const glm::vec2& pivot) noexcept;
    [[nodiscard]] bool IsVisible() const noexcept;
    void SetVisible(bool visible) noexcept;

private:
    std::shared_ptr<Texture> m_texture;
    glm::vec4 m_color = glm::vec4(1.f);
    glm::vec2 m_size = glm::vec2(100.f);
    glm::vec2 m_lowerLeftUV = glm::vec2(0.f);
    glm::vec2 m_upperRightUV = glm::vec2(1.f);
    glm::vec2 m_pivot = glm::vec2(0.5f);
    bool m_visible {true};
};



}