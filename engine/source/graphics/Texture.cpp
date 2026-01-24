#include "graphics/Texture.hpp"

namespace eng
{

Texture::Texture(int width, int height, int numChannels, unsigned char* data)
    : m_width(width), m_height(height), m_numChannels(numChannels) {
    // Create texture in GPU memory and activate it
    glGenTextures(1, &m_textureID);
    glBindTexture(GL_TEXTURE_2D, m_textureID);

    // Load data to the GPU
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);

    // Generate mipmaps (are smaller versions of the same texture)
    glGenerateMipmap(GL_TEXTURE_2D);

    // Texture wrapping: how image behave when it is going outside coordinates 0-1.
    // repeat - mirror repeat - clamp to edge
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

    // Filtering: determines how the texture is scale when the texture is draw smaller or larger
    // than its own resolution.
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
}

Texture::~Texture() {
    if (m_textureID > 0) {
        glDeleteTextures(1, &m_textureID);
    }
}

GLuint Texture::GetID() const {
    return m_textureID;
}

}