#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include <vector>
#include <string>

struct Vec2 {
    float x{0.f};
    float y{0.f};
};

Vec2 offset;

void keyCallback(GLFWwindow* window, int key, int scanCode, int action, int mode) {
    if (action == GLFW_PRESS) {
        switch(key) {
            case GLFW_KEY_UP:
                offset.y += 0.01f;
                std::cout << "GLFW_KEY_UP" << std::endl;
            break;
            case GLFW_KEY_DOWN:
                offset.y -= 0.01f;
                std::cout << "GLFW_KEY_DOWN" << std::endl;
            break;
            case GLFW_KEY_RIGHT:
                offset.x += 0.01f;
                std::cout << "GLFW_KEY_RIGHT" << std::endl;
            break;
            case GLFW_KEY_LEFT:
                offset.x -= 0.01f;
                std::cout << "GLFW_KEY_LEFT" << std::endl;
            break;
            default:
            break;
        }
    }
}

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

    glfwSetKeyCallback(window, keyCallback);

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

    // Declares a vertex input in location 0. 3d vector for each vertex pos
    std::string vertexShaderSource = R"(
        #version 330 core
        layout (location = 0) in vec3 position;
        layout (location = 1) in vec3 color;

        uniform vec2 uOffset;

        out vec3 vColor;

        void main()
        {
            vColor = color;
            gl_Position = vec4(position.x + uOffset.x, position.y + uOffset.y, position.z, 1.0);
        }
    )";
    GLuint vertexShader = glCreateShader(GL_VERTEX_SHADER);
    const char* vertexShaderCStr = vertexShaderSource.c_str();
    glShaderSource(vertexShader, 1, &vertexShaderCStr, nullptr);
    glCompileShader(vertexShader);

    GLint success;
    glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);
    if (!success) {
        char infoLog[512];
        glGetShaderInfoLog(vertexShader, 512, nullptr, infoLog);
        std::cerr << "ERROR: VERTEX_SHADER_COMPILATION_FAILED: " << infoLog << std::endl;
    }

    // output value from the shader
    std::string fragmentShaderSource = R"(
        #version 330 core
        out vec4 FragColor;

        in vec3 vColor;
        uniform vec4 uColor;

        void main()
        {
            FragColor = vec4(vColor, 1.0) * uColor;
        }
    )";

    GLuint fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
    const char* fragmentShaderSourceCstr = fragmentShaderSource.c_str();
    glShaderSource(fragmentShader, 1, &fragmentShaderSourceCstr, nullptr);
    glCompileShader(fragmentShader);

    glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &success);
    if (!success) {
        char infoLog[512];
        glGetShaderInfoLog(fragmentShader, 512, nullptr, infoLog);
        std::cerr << "ERROR: FRAGMENT_SHADER_COMPILATION_FAILED: " << infoLog << std::endl;
    }

    GLuint shaderProgram = glCreateProgram();
    glAttachShader(shaderProgram, vertexShader);
    glAttachShader(shaderProgram, fragmentShader);
    glLinkProgram(shaderProgram);

    glGetProgramiv(shaderProgram, GL_LINK_STATUS, &success);
    if (!success) {
        char infoLog[512];
        glGetProgramInfoLog(shaderProgram, 512, nullptr, infoLog);
        std::cerr << "ERROR: SHADER_PROGRAM_LINKING_FAILED: " << infoLog << std::endl;
    }

    // Once linked, we don't need the program in the gpu so we can free memory.
    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader);

    // Remember: counter clockwise for vertices connection order
    std::vector<float> vertices {
        0.5f, 0.5f, 0.f, 1.f, 0.f, 0.f,
        -0.5f, 0.5f, 0.f, 0.f, 1.f, 0.f,
        -0.5f, -0.5f, 0.f, 0.f, 0.f, 1.f,
        0.5f, -0.5f, 0.f, 1.f, 1.f, 0.f
    };

    std::vector<unsigned int> indices {
        0, 1, 2,
        0, 2, 3
    };

    GLuint vbo;
    glGenBuffers(1, &vbo);
    glBindBuffer(GL_ARRAY_BUFFER, vbo);
    // From system to gpu memory
    glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(float), vertices.data(), GL_STATIC_DRAW);
    glBindBuffer(GL_ARRAY_BUFFER, 0);

    GLuint ebo;
    glGenBuffers(1, &ebo);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(unsigned int), indices.data(), GL_STATIC_DRAW);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

    GLuint vao;
    glGenVertexArrays(1, &vao);
    glBindVertexArray(vao);
    glBindBuffer(GL_ARRAY_BUFFER, vbo);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo);

    glVertexAttribPointer(0, 3, GL_FLOAT, false, 6 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);

    glVertexAttribPointer(1, 3, GL_FLOAT, false, 6 * sizeof(float), (void*)(3 * sizeof(float)));
    glEnableVertexAttribArray(1);

    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);

    GLint uColorLoc = glGetUniformLocation(shaderProgram, "uColor");
    GLuint uOffsetLoc = glGetUniformLocation(shaderProgram, "uOffset");

    while (!glfwWindowShouldClose(window)) {
        glClearColor(1.f, 1.f, 0.f, 1.f);
        glClear(GL_COLOR_BUFFER_BIT);

        glUseProgram(shaderProgram);
        glUniform4f(uColorLoc, 0.f, 1.f, 0.f, 1.f);
        glUniform2f(uOffsetLoc, offset.x, offset.y);
        glBindVertexArray(vao);
        glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);

        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    glfwTerminate();

    return 0;
}