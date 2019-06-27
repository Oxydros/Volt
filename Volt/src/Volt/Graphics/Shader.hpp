#pragma once

#include <memory>

namespace Volt::Graphics
{
    class Shader
    {
    public:
        typedef std::unique_ptr<Shader> ShaderPtr;

    public:
        static ShaderPtr CreateShader(std::string const &vertexSrc, std::string const &pixelSrc);
    public:
        Shader() = default;
        virtual ~Shader() = default;

        virtual void Bind() = 0;
    };
}