#include "graphics/ShaderProgram.hpp"

namespace eng
{

ShaderProgram::ShaderProgram(GLint shaderProgramID)
    : m_shaderProgramID(shaderProgramID) {
}

ShaderProgram::~ShaderProgram() {
    glDeleteProgram(m_shaderProgramID);
}

void ShaderProgram::Bind() {
    glUseProgram(m_shaderProgramID);
}

GLint ShaderProgram::GetUniformLocation(const std::string& name) {
    auto it = m_uniformLocationCache.find(name);
    if (it == m_uniformLocationCache.end()) {
        GLint location = glGetUniformLocation(m_shaderProgramID, name.c_str());
        m_uniformLocationCache[name] = location;
        return location;
    }

    return it->second;
}

void ShaderProgram::SetUniform(const std::string& name, float value) {
    auto location = GetUniformLocation(name);
    glUniform1f(location, value);
}

}