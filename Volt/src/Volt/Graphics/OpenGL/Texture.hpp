#pragma once

#include "Volt/Graphics/Texture.hpp"

namespace Volt::Graphics::OpenGL
{
    class Texture : public Volt::Graphics::Texture
    {
    public:
        Texture();
        virtual ~Texture();

    public:
        void LoadFromFile(std::string const &filePath, bool isAlpha = true) override;
        void LoadFromData(unsigned char *data, int width, int height, bool isAlpha = true) override;
        void Bind(uint8_t slot = 0) override;
        void Unbind(uint8_t slot = 0) override;

        void SetXYWrap(TextureWrap xParam, TextureWrap yParam) override;
        void SetXWrap(TextureWrap type) override;
        void SetYWrap(TextureWrap type) override;

        void SetMinify(TextureMin param) override;
        void SetMagnify(TextureMag param) override;

    private:
        u_int32_t   m_textureId;
    };
}