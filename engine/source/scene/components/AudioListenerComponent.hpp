#pragma once

#include "scene/Component.hpp"

namespace eng
{

class AudioListenerComponent : public Component {
    COMPONENT(AudioListenerComponent)
public:
    void Update(float deltaTime) override;
};

}