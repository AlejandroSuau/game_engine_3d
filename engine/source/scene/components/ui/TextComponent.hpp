#pragma once

#include "scene/components/ui/UIElementComponent.hpp"

#include <string>

namespace eng
{

class TextComponent : public UIElementComponent {
    COMPONENT_2(TextComponent, UIElementComponent)
public:
    void Render(CanvasComponent* element) override;

    void SetText(const std::string& text);
    const std::string& GetText() const;

private:
    std::string m_text;
};

}