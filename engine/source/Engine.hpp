#pragma once

#include "input/InputManager.hpp"
#include "graphics/GraphicsAPI.hpp"
#include "graphics/Texture.hpp"
#include "render/RenderQueue.hpp"
#include "io/FileSystem.hpp"
#include "physics/PhysicsManager.hpp"
#include "audio/AudioManager.hpp"
#include "font/FontManager.hpp"
#include "scene/components/ui/UIInputSystem.hpp"

#include <memory>
#include <chrono>

struct GLFWwindow;
namespace eng
{

class Scene;
class Application;

class Engine {
public:
    static Engine& GetInstance();

    bool Init(int width, int height);
    void Run();
    void Destroy();
    void SetCursorEnabled(bool enabled);
    
    void SetApplication(Application* app);
    Application* GetApplication();
    InputManager& GetInputManager();
    GraphicsAPI& GetGraphicsAPI();
    RenderQueue& GetRenderQueue();
    FileSystem& GetFileSystem();
    TextureManager& GetTextureManager();
    PhysicsManager& GetPhysicsManager();
    AudioManager& GetAudioManager();
    FontManager& GetFontManager();
    UIInputSystem& GetUIInputSystem();

    void SetScene(const std::shared_ptr<Scene>& scene);
    const std::shared_ptr<Scene>& GetScene();

private:
    Engine() = default;
    Engine(const Engine&) = delete;
    Engine(Engine&&) = delete;
    Engine& operator=(const Engine&) = delete;
    Engine& operator=(Engine&&) = delete;

    std::unique_ptr<Application> m_application;
    std::chrono::steady_clock::time_point m_lastTimePoint;
    GLFWwindow* m_window = nullptr;
    InputManager m_inputManager;
    GraphicsAPI m_graphicsAPI;
    RenderQueue m_renderQueue;
    FileSystem m_fileSystem;
    TextureManager m_textureManager;
    PhysicsManager m_physicsManager;
    AudioManager m_audioManager;
    FontManager m_fontManager;
    UIInputSystem m_uiInputSystem;
    std::shared_ptr<Scene> m_currentScene;
};

}