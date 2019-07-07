#pragma once

#include <string>
#include <memory>

namespace Volt::Graphics
{
    enum class TextureWrap : uint8_t
    {
        REPEAT, MIRROR_REPEAT, CLAMP
    };

    enum class TextureMin : uint8_t
    {
        NEAREST, LINEAR,
        NEAREST_MIPMAP_NEAREST, LINEAR_MIPMAP_NEAREST,
        NEAREST_MIPMAP_LINEAR, LINEAR_MIPMAP_LINEAR
    };

    enum class TextureMag : uint8_t
    {
        NEAREST, LINEAR
    };

    class Texture
    {
    public:
        typedef std::shared_ptr<Texture> TexturePtr;

    public:
        static TexturePtr CreateFromFile(std::string const &filePath, bool isAlpha= true);
        static TexturePtr CreateFromData(unsigned char *data, int width, int height, bool isAlpha = true);

    public:
        Texture() = default;
        virtual ~Texture() = default;

    public:
        virtual void LoadFromFile(std::string const &filePath, bool isAlpha) = 0;
        virtual void LoadFromData(unsigned char *data, int width, int height, bool isAlpha) = 0;
        virtual void Bind(uint8_t slot) = 0;
        virtual void Unbind(uint8_t slot) = 0;

        virtual void SetXYWrap(TextureWrap xParam, TextureWrap yParam) = 0;
        virtual void SetXWrap(TextureWrap param) = 0;
        virtual void SetYWrap(TextureWrap param) = 0;

        virtual void SetMinify(TextureMin param) = 0;
        virtual void SetMagnify(TextureMag param) = 0;
    };
}