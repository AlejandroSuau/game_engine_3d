#pragma once

#include "scene/GameObject.hpp"
#include "EngineCommon.hpp"

#include <vector>
#include <string>
#include <memory>

namespace eng
{

class Scene
{
public:
    void Update(float deltaTime);
    void Clear();
    
    GameObject* CreateObject(const std::string& name, GameObject* parent = nullptr);

    template<typename T, typename = typename std::enable_if_t<std::is_base_of_v<GameObject, T>>>
    T* CreateObject(const std::string& name, GameObject* parent = nullptr) {
        auto obj = new T();
        obj->SetName(name);
        SetParent(obj, parent);

        return obj;
    }

    bool SetParent(GameObject* obj, GameObject* parent);
    void SetMainCamera(GameObject* camera);
    GameObject* GetMainCamera();

    std::vector<LightData> CollectLights();

private:
    std::vector<std::unique_ptr<GameObject>> m_objects;
    GameObject* m_mainCamera {nullptr};

    void CollectLightsRecursive(GameObject* obj, std::vector<LightData>& out);
};

}