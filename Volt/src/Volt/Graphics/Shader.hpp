#pragma once

#include <memory>
#include <glm/glm.hpp>

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

        //TODO === Improve this
        virtual void SetInt(std::string const &uniform_name, int value) = 0;

        virtual void SetFloat(std::string const &uniform_name, float value) = 0;
        virtual void SetVec3f(std::string const &uniform_name, glm::vec3 const &value) = 0;
        virtual void SetVec4f(std::string const &uniform_name, glm::vec4 const &value) = 0;

        virtual void SetMat3f(std::string const &uniform_name, glm::mat3 const &value) = 0;
        virtual void SetMat4f(std::string const &uniform_name, glm::mat4 const &value) = 0;
    };
}