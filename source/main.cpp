#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include <vector>
#include <string>

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

    // Vertex Data -> Vertex Shader -> Primitive Assembly -> Rasterization -> Fragment shader -> Testing & blending -> Screen buffer
    
    // **** Programable stages were we have the most control

    // - Vertex Shader ****
    // A program that runs in the GPU (receives a group of points / vertices from the screen space)
    // Forming the shape of an object or mesh.

    // - Primitive Assembly
    // Vertices are assembled into complete triangles.

    // - Rasterization
    // Takes the primities and fill the area with pixels called fragments. The output is
    // a ollection of fragments that covers the area of the shape.

    // - Fragment Shader ****
    // Another GPU program. It works with individual fragments. Determines the color of each
    // pixel, so it helps to color different parts of an object.

    // - Testing & Blending
    // This ensures that new pixels are correctly combined with what was already in the frame
    // buffer.

    // And once its done the result is displayed in the screen buffer.

    // Remember: counter clockwise for vertices connection order
    std::vector<float> vertices {
        0.f, 0.5f, 0.f,
        -0.5f, -0.5f, 0.f,
        0.5f, -0.5f, 0.f
    };

    while (!glfwWindowShouldClose(window)) {
        glClearColor(1.f, 0.f, 0.f, 1.f);
        glClear(GL_COLOR_BUFFER_BIT);

        glfwSwapBuffers(window);

        glfwPollEvents();
    }

    glfwTerminate();

    return 0;
}