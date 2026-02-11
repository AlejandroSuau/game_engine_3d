#include "scene/components/ui/CanvasComponent.hpp"

#include "scene/components/ui/UIElementComponent.hpp"
#include "scene/GameObject.hpp"

namespace eng
{

void CanvasComponent::Update(float deltaTime) {
    const auto& children = m_owner->GetChildren();
    for (const auto& child : children) {
        if (auto comp = child->GetComponent<UIElementComponent>()) {
            Render(comp);
        }
    }
}

void CanvasComponent::Render(UIElementComponent* element) {
    if (!element) return;

    element->Render(this);
    const auto& children = element->GetOwner()->GetChildren();
    for (const auto& child : children) {
        if (auto comp = child->GetComponent<UIElementComponent>()) {
            Render(comp);
        }
    }
}

}