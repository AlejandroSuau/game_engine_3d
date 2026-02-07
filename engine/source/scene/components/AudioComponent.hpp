#pragma once

#include "scene/Component.hpp"
#include "audio/Audio.hpp"

namespace eng
{

class AudioComponent : public Component {
    COMPONENT(AudioComponent)
public:
    AudioComponent() = default;

    void LoadProperties(const nlohmann::json& json) override;
    void Update(float deltaTime) override;

    void RegisterAudio(const std::string& name, std::shared_ptr<Audio>& clip);
    void Play(const std::string& name, bool loop = false);
    void Stop(const std::string& name);
    bool IsPlaying(const std::string& name) const;

private:
    std::unordered_map<std::string, std::shared_ptr<Audio>> m_clips;
};

}