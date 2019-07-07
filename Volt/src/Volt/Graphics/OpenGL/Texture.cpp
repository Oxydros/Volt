#include "vpch.h"
#include "Volt/Graphics/OpenGL/Texture.hpp"

#include <glad/glad.h>
#include <stb_image.h>

GLenum TextureWrapToOpenGL(Volt::Graphics::TextureWrap type)
{
    switch (type)
    {
        case Volt::Graphics::TextureWrap::REPEAT: return GL_REPEAT;
        case Volt::Graphics::TextureWrap::MIRROR_REPEAT: return GL_MIRRORED_REPEAT;
        case Volt::Graphics::TextureWrap::CLAMP: return GL_CLAMP_TO_EDGE;
        default:
        {
            VOLT_ASSERT(false, "Unknown TextureWrap type !");
        }
    }
}

GLenum TextureMinToOpenGL(Volt::Graphics::TextureMin type)
{
    switch (type)
    {
        case Volt::Graphics::TextureMin::NEAREST: return GL_NEAREST;
        case Volt::Graphics::TextureMin::LINEAR: return GL_LINEAR;
        case Volt::Graphics::TextureMin::NEAREST_MIPMAP_NEAREST: return GL_NEAREST_MIPMAP_NEAREST;
        case Volt::Graphics::TextureMin::LINEAR_MIPMAP_NEAREST: return GL_LINEAR_MIPMAP_NEAREST;
        case Volt::Graphics::TextureMin::NEAREST_MIPMAP_LINEAR: return GL_NEAREST_MIPMAP_LINEAR;
        case Volt::Graphics::TextureMin::LINEAR_MIPMAP_LINEAR: return GL_LINEAR_MIPMAP_LINEAR;
        default:
        {
            VOLT_ASSERT(false, "Unknown TextureMin type !");
        }
    }
}

GLenum TextureMagToOpenGL(Volt::Graphics::TextureMag type)
{
    switch (type)
    {
        case Volt::Graphics::TextureMag::NEAREST: return GL_NEAREST;
        case Volt::Graphics::TextureMag::LINEAR: return GL_LINEAR;
        default:
        {
            VOLT_ASSERT(false, "Unknown TextureMag type !");
        }
    }
}

namespace Volt::Graphics::OpenGL
{
    Texture::Texture()
    {
        glGenTextures(1, &m_textureId);
    }

    Texture::~Texture()
    {
        glDeleteTextures(1, &m_textureId);
    }

    void Texture::LoadFromFile(std::string const &filePath, bool isAlpha)
    {
        unsigned char *data;
        int width, height, nrChannels;
        stbi_set_flip_vertically_on_load(true);      

        data = stbi_load(filePath.c_str(), &width, &height, &nrChannels, isAlpha ? STBI_rgb_alpha : STBI_rgb);
        if (!data)
            VOLT_ASSERT(false, "Coudln't load image: {}", filePath);

        glBindTexture(GL_TEXTURE_2D, m_textureId);
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, isAlpha ? GL_RGBA : GL_RGB, GL_UNSIGNED_BYTE, data);
        glGenerateMipmap(GL_TEXTURE_2D);

        stbi_image_free(data);
    }

    void Texture::LoadFromData(unsigned char *data, int width, int height, bool isAlpha)
    {
        glBindTexture(GL_TEXTURE_2D, m_textureId);
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, isAlpha ? GL_RGBA : GL_RGB, GL_UNSIGNED_BYTE, data);
    }

    void Texture::Bind(uint8_t slot)
    {
        glActiveTexture(GL_TEXTURE0 + slot);
        glBindTexture(GL_TEXTURE_2D, m_textureId);
    }

    void Texture::Unbind(uint8_t slot)
    {
        glActiveTexture(GL_TEXTURE0 + slot);
        glBindTexture(GL_TEXTURE_2D, 0);
    }

    void Texture::SetXYWrap(TextureWrap xParam, TextureWrap yParam)
    {
        glBindTexture(GL_TEXTURE_2D, m_textureId);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, TextureWrapToOpenGL(xParam));
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, TextureWrapToOpenGL(yParam));
    }

    void Texture::SetXWrap(TextureWrap param)
    {
        glBindTexture(GL_TEXTURE_2D, m_textureId);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, TextureWrapToOpenGL(param));
    }

    void Texture::SetYWrap(TextureWrap param)
    {
        glBindTexture(GL_TEXTURE_2D, m_textureId);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, TextureWrapToOpenGL(param));
    }

    void Texture::SetMinify(TextureMin param)
    {
        glBindTexture(GL_TEXTURE_2D, m_textureId);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, TextureMinToOpenGL(param));
    }

    void Texture::SetMagnify(TextureMag param)
    {
        glBindTexture(GL_TEXTURE_2D, m_textureId);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, TextureMagToOpenGL(param));
    }
}

Volt::Graphics::Texture::TexturePtr Volt::Graphics::Texture::CreateFromFile(std::string const &filePath, bool isAlpha)
{
    auto ptr = std::make_shared<Volt::Graphics::OpenGL::Texture>();
    ptr->LoadFromFile(filePath, isAlpha);
    return ptr;
}

Volt::Graphics::Texture::TexturePtr Volt::Graphics::Texture::CreateFromData(unsigned char *data, int width, int height, bool isAlpha)
{
    auto ptr = std::make_shared<Volt::Graphics::OpenGL::Texture>();
    ptr->LoadFromData(data, width, height, isAlpha);
    return ptr;
}