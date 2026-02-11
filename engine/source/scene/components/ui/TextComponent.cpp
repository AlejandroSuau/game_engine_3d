#include "scene/components/ui/TextComponent.hpp"

#include <string>

namespace eng
{

void TextComponent::Render(CanvasComponent* element) {

}

void TextComponent::SetText(const std::string& text) {
    m_text = text;
}

const std::string& TextComponent::GetText() const {
    return m_text;
}

}