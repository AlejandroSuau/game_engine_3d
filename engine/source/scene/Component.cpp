#include "scene/Component.hpp"

namespace eng
{

GameObject* Component::GetOwner() {
    return m_owner;
}

}