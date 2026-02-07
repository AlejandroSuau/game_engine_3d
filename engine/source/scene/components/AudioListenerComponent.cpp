#include "scene/components/AudioListenerComponent.hpp"

#include "scene/GameObject.hpp"
#include "Engine.hpp"

namespace eng
{

void AudioListenerComponent::Update(float deltaTime) {
    auto pos = m_owner->GetWorldPosition();
    Engine::GetInstance().GetAudioManager().SetListenerPosition(pos);
}

}