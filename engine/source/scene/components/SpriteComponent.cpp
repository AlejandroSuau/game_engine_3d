#include "scene/components/SpriteComponent.hpp"

#include "graphics/Texture.hpp"
#include "render/RenderQueue.hpp"
#include "scene/GameObject.hpp"
#include "Engine.hpp"

#include <string>

namespace eng
{

void SpriteComponent::LoadProperties(const nlohmann::json& json) {
    // Texture
    const std::string texturePath = json.value("texture", "");
    if (auto texture = Texture::Load(texturePath)) {
        SetTexture(texture);
    }

    // Color
    if (json.contains("color")) {
        auto& colorObj = json["color"];
        glm::vec4 color(
            colorObj.value("r", 1.f),
            colorObj.value("g", 1.f),
            colorObj.value("b", 1.f),
            colorObj.value("a", 1.f)
        );
        SetColor(color);
    }

    // Size
    if (json.contains("size")) {
        auto& sizeObj = json["size"];
        glm::vec2 size(
            sizeObj.value("x", 100.f),
            sizeObj.value("y", 100.f)
        );
        SetSize(size);
    }

    // Lower Left UV
    if (json.contains("lowerLeftUV")) {
        auto& uvObj = json["lowerLeftUV"];
        glm::vec2 uv(
            uvObj.value("u", 0.f),
            uvObj.value("v", 0.f)
        );
        SetLowerLeftUV(uv);
    }

    // Upper right UV
    if (json.contains("upperRightUV")) {
        auto& uvObj = json["upperRightUV"];
        glm::vec2 uv(
            uvObj.value("u", 1.f),
            uvObj.value("v", 1.f)
        );
        SetUpperRightUV(uv);
    }

    // Pivot
    if (json.contains("pivot")) {
        auto& pivotObj = json["pivot"];
        glm::vec2 pivot(
            pivotObj.value("x", 0.5f),
            pivotObj.value("y", 0.5f)
        );
        SetPivot(pivot);
    }
}

void SpriteComponent::Update(float deltaTime) {
    if (!m_texture || !m_visible) { return; }

    RenderCommand2D command;
    command.modelMatrix = GetOwner()->GetWorldTransform2D();
    command.texture = m_texture.get();
    command.color = m_color;
    command.size = m_size;
    command.lowerLeftUV = m_lowerLeftUV;
    command.upperRightUV = m_upperRightUV;
    command.pivot = m_pivot;
    
    auto& renderQueue = Engine::GetInstance().GetRenderQueue();
    renderQueue.Submit(command);
}

const std::shared_ptr<Texture>& SpriteComponent::GetTexture() const noexcept {
    return m_texture;
}

void SpriteComponent::SetTexture(const std::shared_ptr<Texture>& texture) noexcept {
    m_texture = texture;
}

const glm::vec4& SpriteComponent::GetColor() const noexcept {
    return m_color;
}

void SpriteComponent::SetColor(const glm::vec4& color) noexcept {
    m_color = color;
}

const glm::vec2& SpriteComponent::GetSize() const noexcept {
    return m_size;
}

void SpriteComponent::SetSize(const glm::vec2& size) noexcept {
    m_size = size;
}

void SpriteComponent::SetUV(const glm::vec2& lowerLeftUV, const glm::vec2& upperRightUV) noexcept {
    m_lowerLeftUV = lowerLeftUV;
    m_upperRightUV = upperRightUV;
}

const glm::vec2& SpriteComponent::GetLowerLeftUV() const noexcept {
    return m_lowerLeftUV;
}

void SpriteComponent::SetLowerLeftUV(const glm::vec2& uv) noexcept {
    m_lowerLeftUV = uv;
}

const glm::vec2& SpriteComponent::GetUpperRightUV() const noexcept {
    return m_upperRightUV;
}

void SpriteComponent::SetUpperRightUV(const glm::vec2& uv) noexcept {
    m_upperRightUV = uv;
}

const glm::vec2& SpriteComponent::GetPivot() const noexcept {
    return m_pivot;
}

void SpriteComponent::SetPivot(const glm::vec2& pivot) noexcept {
    m_pivot = pivot;
}

bool SpriteComponent::IsVisible() const noexcept {
    return m_visible;
}

void SpriteComponent::SetVisible(bool visible) noexcept {
    m_visible = visible;
}

}