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

        void SetInt(std::string const &uniform_name, int value) override;

        void SetFloat(std::string const &uniform_name, float value) override;
        void SetVec3f(std::string const &uniform_name, glm::vec3 const &value) override;
        void SetVec4f(std::string const &uniform_name, glm::vec4 const &value) override;

        void SetMat3f(std::string const &uniform_name, glm::mat3 const &value) override;
        void SetMat4f(std::string const &uniform_name, glm::mat4 const &value) override;

    private:
        uint32_t    m_programId;
    };
}