#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <iostream>

int main() {
    if (!glfwInit()) {
        return -1;
    }

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    GLFWwindow* window = glfwCreateWindow(1200, 720, "GameEngine3D", nullptr, nullptr);
    if (!window) {
        std::cout << "Error creating window" << std::endl;
        glfwTerminate();
        return -1;
    }

    glfwSetWindowPos(window, 750, 150);
    glfwMakeContextCurrent(window);

    if (glewInit() != GLEW_OK) {
        glfwTerminate();
        return -1;
    }

    while (!glfwWindowShouldClose(window)) {
        glClearColor(1.f, 0.f, 0.f, 1.f);
        glClear(GL_COLOR_BUFFER_BIT);

        glfwSwapBuffers(window);

        glfwPollEvents();
    }

    glfwTerminate();

    return 0;
}