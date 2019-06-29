#include "vpch.h"

#include "Volt/Graphics/OpenGL/Shader.hpp"

#include <glad/glad.h>

namespace Volt::Graphics::OpenGL
{
    Shader::Shader(std::string const &vertexSrc, std::string const &pixelSrc)
        : m_programId(0)
    {

        int  success;
        char infoLog[512];

        GLuint vertexShaderID = glCreateShader(GL_VERTEX_SHADER);
        VOLT_ASSERT(vertexShaderID != 0, "Couldn't create vertex Shader")


        const GLchar *src = vertexSrc.c_str();

        glShaderSource(vertexShaderID, 1, &src, NULL);
        glCompileShader(vertexShaderID);

        glGetShaderiv(vertexShaderID, GL_COMPILE_STATUS, &success);

        if(!success)
        {
            glGetShaderInfoLog(vertexShaderID, 512, NULL, infoLog);
            VOLT_ASSERT(false, "Error while COMPILING vertex shader : {}", infoLog);
        }

        GLuint pixelShaderID = glCreateShader(GL_FRAGMENT_SHADER);
        VOLT_ASSERT(pixelShaderID != 0, "Couldn't create pixel Shader")


        src = pixelSrc.c_str();

        glShaderSource(pixelShaderID, 1, &src, NULL);
        glCompileShader(pixelShaderID);

        glGetShaderiv(pixelShaderID, GL_COMPILE_STATUS, &success);

        if(!success)
        {
            glGetShaderInfoLog(pixelShaderID, 512, NULL, infoLog);
            VOLT_ASSERT(false, "Error while COMPILING pixel shader : {}", infoLog);
        }

        m_programId = glCreateProgram();

        glAttachShader(m_programId, vertexShaderID);
        glAttachShader(m_programId, pixelShaderID);
        glLinkProgram(m_programId);

        glGetProgramiv(m_programId, GL_LINK_STATUS, &success);
        if(!success) {
            glGetProgramInfoLog(m_programId, 512, NULL, infoLog);
            VOLT_ASSERT(false, "Error while LINKING shaders in program : {}", infoLog);
        }

        glDeleteShader(vertexShaderID);
        glDeleteShader(pixelShaderID);
    }

    Shader::~Shader()
    {
        glDeleteProgram(m_programId);
    }

    void Shader::Bind()
    {
        glUseProgram(m_programId);
    }

    void Shader::SetFloat(std::string const &uniform_name, float value)
    {
        int uniformLocation = glGetUniformLocation(m_programId, uniform_name.c_str());
        VOLT_ASSERT(uniformLocation != -1, "Unable to find uniform {} in shader", uniform_name);
        glUseProgram(m_programId);
        glUniform1f(uniformLocation, value);
    }

    void Shader::SetVec3f(std::string const &uniform_name, glm::vec3 const &value)
    {
        int uniformLocation = glGetUniformLocation(m_programId, uniform_name.c_str());
        VOLT_ASSERT(uniformLocation != -1, "Unable to find uniform {} in shader", uniform_name);
        glUseProgram(m_programId);
        glUniform3f(uniformLocation, value.x, value.y, value.z);
    }

    void Shader::SetVec4f(std::string const &uniform_name, glm::vec4 const &value)
    {
        int uniformLocation = glGetUniformLocation(m_programId, uniform_name.c_str());
        VOLT_ASSERT(uniformLocation != -1, "Unable to find uniform {} in shader", uniform_name);
        glUseProgram(m_programId);
        glUniform4f(uniformLocation, value.x, value.y, value.z, value.w);
    }
}

Volt::Graphics::Shader::ShaderPtr Volt::Graphics::Shader::CreateShader(std::string const &vertexSrc, std::string const &pixelSrc)
{
    return std::make_unique<Volt::Graphics::OpenGL::Shader>(vertexSrc, pixelSrc);
}