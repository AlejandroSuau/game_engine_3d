#include "graphics/GraphicsAPI.hpp"

#include "graphics/ShaderProgram.hpp"
#include "render/Material.hpp"
#include "render/Mesh.hpp"

#include <iostream>

namespace eng
{

bool GraphicsAPI::Init() {
    glEnable(GL_DEPTH_TEST);
    return true;
}

std::shared_ptr<ShaderProgram> GraphicsAPI::CreateShaderProgram(
    const std::string& vertexSource,
    const std::string& fragmentSource) {
    // Compile shaders
    GLuint vertexShader = glCreateShader(GL_VERTEX_SHADER);
    const char* vertexShaderCStr = vertexSource.c_str();
    glShaderSource(vertexShader, 1, &vertexShaderCStr, NULL);
    glCompileShader(vertexShader);

    // Check vertex shader compilation    
    GLint success;
    char infoLog[512];
    glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);
    if (!success) {
        glGetShaderInfoLog(vertexShader, 512, nullptr, infoLog);
        std::cerr << "ERROR: VERTEX_SHADER_COMPILATION_FAILED: " << infoLog << std::endl;
        return nullptr;
    }

    GLuint fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
    const char* fragmentShaderSourceCstr = fragmentSource.c_str();
    glShaderSource(fragmentShader, 1, &fragmentShaderSourceCstr, nullptr);
    glCompileShader(fragmentShader);

    // Check vertex shader compilation
    glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &success);
    if (!success) {
        glGetShaderInfoLog(fragmentShader, 512, nullptr, infoLog);
        std::cerr << "ERROR: FRAGMENT_SHADER_COMPILATION_FAILED: " << infoLog << std::endl;
        return nullptr;
    }

    // Create shader program
    GLuint shaderProgramID = glCreateProgram();
    glAttachShader(shaderProgramID, vertexShader);
    glAttachShader(shaderProgramID, fragmentShader);
    glLinkProgram(shaderProgramID);

    // Check shader program
    glGetProgramiv(shaderProgramID, GL_LINK_STATUS, &success);
    if (!success) {
        glGetProgramInfoLog(shaderProgramID, 512, nullptr, infoLog);
        std::cerr << "ERROR: SHADER_PROGRAM_LINKING_FAILED: " << infoLog << std::endl;
        return nullptr;
    }

    // Cleanup shaders
    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader);

    return std::make_shared<ShaderProgram>(shaderProgramID);
}

void GraphicsAPI::BindShaderProgram(ShaderProgram* shaderProgram) {
    if (!shaderProgram) {
        return;
    }

    shaderProgram->Bind();
}

void GraphicsAPI::BindMaterial(Material* material) {
    if (!material) {
        return;
    }

    material->Bind();
}

void GraphicsAPI::BindMesh(Mesh* mesh) {
    if (!mesh) return;
    
    mesh->Bind();
}

void GraphicsAPI::DrawMesh(Mesh* mesh) {
    if (!mesh) return;
    
    mesh->Draw();
}

GLuint GraphicsAPI::CreateVertexBuffer(const std::vector<float>& vertices) {
    GLuint VBO = 0;
    glGenBuffers(1, &VBO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(float), vertices.data(), GL_STATIC_DRAW);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    
    return VBO;
}

GLuint GraphicsAPI::CreateIndexBuffer(const std::vector<uint32_t>& indices) {
    GLuint EBO = 0;
    glGenBuffers(1, &EBO);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(uint32_t), indices.data(), GL_STATIC_DRAW);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
    
    return EBO;
}

void GraphicsAPI::SetClearColor(float r, float g, float b, float a) {
    glClearColor(r, g, b, a);
}

void GraphicsAPI::ClearBuffers() {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

}