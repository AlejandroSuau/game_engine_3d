#include "Engine.hpp"
#include "Application.hpp"

#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include <iostream> 

namespace eng
{

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

    glfwMakeContextCurrent(m_window);

    // Initialize GLEW
    if (glewInit() != GLEW_OK) {
        std::cout << "Error initializing GLEW" << std::endl; 
        glfwTerminate();
        return false;
    }

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

        glfwSwapBuffers(m_window);
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

}