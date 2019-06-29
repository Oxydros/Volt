#pragma once

#include "Volt/Graphics/Shader.hpp"

namespace Volt::Graphics::OpenGL
{
    class Shader : public Volt::Graphics::Shader
    {
    public:
        Shader(std::string const &vertexSrc, std::string const &pixelSrc);
        virtual ~Shader();

        void Bind() override;

    private:
        uint32_t    m_programId;
    };
}