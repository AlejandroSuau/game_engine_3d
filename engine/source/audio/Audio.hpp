#pragma once

#include "EngineCommon.hpp"

#include <glm/glm.hpp>

#include <string>
#include <vector>
#include <memory>

struct ma_sound;
struct ma_decoder;

namespace eng
{

class Audio {
public:
    ~Audio();
    void Play(bool loop = false);
    void Stop();
    bool IsPlaying() const;
    void SetVolume(float volume);
    void SetPosition(const glm::vec3& position);
    float GetVolume() const;

    static std::shared_ptr<Audio> Load(const std::string& path);

private:
    std::unique_ptr<ma_sound> m_sound;
    std::unique_ptr<ma_decoder> m_decoder;
    std::vector<char> m_buffer;
};

}