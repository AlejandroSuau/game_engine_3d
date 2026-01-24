#include "Engine.hpp"

#include "Application.hpp"
#include "EngineCommon.hpp"

#include "scene/Scene.hpp"
#include "scene/GameObject.hpp"
#include "scene/Component.hpp"
#include "scene/components/CameraComponent.hpp"

#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include <iostream> 

namespace eng
{

void keyCallback(GLFWwindow* window, int key, int scancode, int action, int mods) {
    InputManager& inputManager = Engine::GetInstance().GetInputManager();

    if (action == GLFW_PRESS) {
        inputManager.SetKeyPressed(key, true);
    } else if (action == GLFW_RELEASE) {
        inputManager.SetKeyPressed(key, false);
    }
}

void mouseButtonCallback(GLFWwindow* window, int button, int action, int mods) {
    InputManager& inputManager = Engine::GetInstance().GetInputManager();
    
    if (action == GLFW_PRESS) {
        inputManager.SetMouseButtonPressed(button, true);
    } else if (action == GLFW_RELEASE) {
        inputManager.SetMouseButtonPressed(button, false);
    }
}

void cursorPositionCallback(GLFWwindow* window, double xpos, double ypos) { 
    InputManager& inputManager = Engine::GetInstance().GetInputManager();
    inputManager.SetMousePositionOld(inputManager.GetMousePositionCurrent());

    glm::vec2 currentPos(static_cast<float>(xpos), static_cast<float>(ypos));
    inputManager.SetMousePositionCurrent(currentPos);
}

Engine& Engine::GetInstance() {
    static Engine instance;
    return instance;
}

bool Engine::Init(int width, int height) {
    if (!m_application) {
        return false;
    }

    // Initialize GLFW
    if (!glfwInit()) {
        std::cout << "Error initializing GLFW" << std::endl;
        return false;
    }

    // Configure GLFW
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);

    // Create window
    m_window = glfwCreateWindow(width, height, "Engine3D", nullptr, nullptr);
    if (!m_window) {
        std::cout << "Error creating window" << std::endl;
        glfwTerminate();
        return false;
    }

    glfwSetKeyCallback(m_window, keyCallback);
    glfwSetMouseButtonCallback(m_window, mouseButtonCallback);
    glfwSetCursorPosCallback(m_window, cursorPositionCallback);

    glfwMakeContextCurrent(m_window);

    // Initialize GLEW
    if (glewInit() != GLEW_OK) {
        std::cout << "Error initializing GLEW" << std::endl; 
        glfwTerminate();
        return false;
    }

    m_graphicsAPI.Init();

    return m_application->Init();
}

void Engine::Run() {
    if (!m_application) {
        return;
    }
    
    m_lastTimePoint = std::chrono::high_resolution_clock::now();
    while (!glfwWindowShouldClose(m_window) && 
           !m_application->NeedsToBeClosed()) {
        
        glfwPollEvents();

        auto now = std::chrono::high_resolution_clock::now();
        float deltaTime = std::chrono::duration<float>(now - m_lastTimePoint).count();
        m_lastTimePoint = now;

        m_application->Update(deltaTime);

        m_graphicsAPI.SetClearColor(1.f, 1.f, 1.f, 1.f);
        m_graphicsAPI.ClearBuffers();

        CameraData cameraData;
        std::vector<LightData> lights;
        int width = 0, height = 0;
        glfwGetWindowSize(m_window, &width, &height);
        float aspectRatio = static_cast<float>(width) / static_cast<float>(height);
        if (m_currentScene) {
            if (auto cameraObject = m_currentScene->GetMainCamera()) {
                // Logic for matrices
                auto cameraComponent = cameraObject->GetComponent<CameraComponent>();
                if (cameraComponent) {
                    cameraData.viewMatrix = cameraComponent->GetViewMatrix();
                    cameraData.projectionMatrix = cameraComponent->GetProjectionMatrix(aspectRatio);
                }
            }

            lights = m_currentScene->CollectLights();
        }

        m_renderQueue.Draw(m_graphicsAPI, cameraData, lights);

        glfwSwapBuffers(m_window);

        m_inputManager.SetMousePositionOld(m_inputManager.GetMousePositionCurrent());
    }
}

void Engine::Destroy() {
    if (m_application) {
        m_application->Destroy();
        m_application.reset();
        glfwTerminate();
        m_window = nullptr;
    }
}

void Engine::SetApplication(Application* app) {
    m_application.reset(app);
}

Application* Engine::GetApplication() {
    return m_application.get();
}

InputManager& Engine::GetInputManager() {
    return m_inputManager;
}

GraphicsAPI& Engine::GetGraphicsAPI() {
    return m_graphicsAPI;
}

RenderQueue& Engine::GetRenderQueue() {
    return m_renderQueue;
}

FileSystem& Engine::GetFileSystem() {
    return m_fileSystem;
}

void Engine::SetScene(Scene* scene) {
    m_currentScene.reset(scene);
}

Scene* Engine::GetScene() {
    return m_currentScene.get();
}

}