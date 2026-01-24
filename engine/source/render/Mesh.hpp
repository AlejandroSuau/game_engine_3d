#pragma once

#include <GL/glew.h>

#include "graphics/VertexLayout.hpp"

#include <memory>
#include <string>

namespace eng
{

class Mesh {
public:
    Mesh(VertexLayout layout, 
        const std::vector<float>& vertices,
        const std::vector<uint32_t>& indices);
    Mesh(VertexLayout layout, 
        const std::vector<float>& vertices);

    Mesh(const Mesh&) = delete;
    Mesh& operator=(const Mesh&) = delete;

    void Bind();
    void Draw();

    static std::shared_ptr<Mesh> CreateCube();
    static std::shared_ptr<Mesh> Load(const std::string& path);
    
private:
    VertexLayout m_vertexLayout;
    GLuint m_VBO {0};// for vertices
    GLuint m_EBO {0};// for indices
    GLuint m_VAO {0};// for vertex array object

    std::size_t m_vertexCount {0};
    std::size_t m_indexCount {0};
};

}