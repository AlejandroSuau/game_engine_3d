#include "graphics/Texture.hpp"

#include "Engine.hpp"
#include "io/FileSystem.hpp"

#define STB_IMAGE_IMPLEMENTATION
#include <stb_image.h>

#include <iostream>

namespace eng
{

Texture::Texture(int width, int height, int numChannels, unsigned char* data)
    : m_width(width), m_height(height), m_numChannels(numChannels) {
    Init(width, height, numChannels, data);
}

void Texture::Init(int width, int height, int numChannels, unsigned char* data) {
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

std::shared_ptr<Texture> Texture::Load(const std::string& path) {
    int width, height, numChannels;
    
    auto& fs = Engine::GetInstance().GetFileSystem();
    auto fullPath = fs.GetAssetsFolder() / path;

    if (!std::filesystem::exists(fullPath)) {
        return nullptr;
    }

    std::shared_ptr<Texture> result;
    unsigned char* data = stbi_load(fullPath.string().c_str(), &width, &height, &numChannels, 0);
    if (data) {
        result = std::make_shared<Texture>(width, height, numChannels, data);
        std::cout << "[Image loaded: " << fullPath.string().c_str() << "]" << std::endl;
        stbi_image_free(data);
    }

    return result;
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