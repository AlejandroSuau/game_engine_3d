#pragma once

#include <GL/glew.h>

#include <vector>

namespace eng
{

struct VertexElement
{
    GLuint index; // Attribute location
    GLuint size; // Number of components
    GLuint type; // datatype (e.g. GL_FLOAT)
    uint32_t offset; // Bytes offset
};

struct VertexLayout
{
    std::vector<VertexElement> elements;
    uint32_t stride = 0; // Total size of a vertex data
};

}